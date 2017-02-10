#include <iostream>
#include <IMiddleware.h>
#include <HttpMethods.h>
#include "Server.h"
#include "HttpParser.h"
#include "json.hpp"

typedef std::function<void(const HttpParser::HttpRequest &req, HttpParser::HttpResponse &res)> RequestHandler;

class Logger : public IMiddleware {
    virtual void handle(HttpParser::HttpRequest &req, HttpParser::HttpResponse &res) const override {
        std::cout << req.method << " " << req.path << std::endl;
    };
};

class Route {
public:
    Route(const std::string &path) : path(path) {

    }

    bool handlesMethod(HTTP_Method method) const {
        return methodHandlers[method] != nullptr;
    }

    Route &get(RequestHandler handler) {
        methodHandlers[GET] = handler;

        return *this;
    }

    Route &put(RequestHandler handler) {
        methodHandlers[PUT] = handler;

        if(methodHandlers[PUT] == nullptr) {
            std::cout << "STill null";
        }
        else {
            std::cout << "Not Null";
        }

        return *this;
    }

    Route &del(RequestHandler handler) {
        methodHandlers[DELETE] = handler;
        return *this;
    }

    bool pathMatches(const std::string &urlPath) const {
        size_t pathPos = urlPath.find(path.c_str(), 0, path.size());
        return pathPos != std::string::npos;
    }

    void handle(HttpParser::HttpRequest &req, HttpParser::HttpResponse &res) const {
        std::map<std::string, HTTP_Method> methodEnumMap = {
                {"GET",    GET},
                {"PUT",    PUT},
                {"DELETE", DELETE},
        };

        HTTP_Method method = methodEnumMap[req.method];
        if (handlesMethod(method)) {
            RequestHandler handler = methodHandlers[method];
            handler(req, res);
        } else {
            std::cout << method << " Don't handle";
        }
    }

    std::array<RequestHandler, METHOD_NUM> methodHandlers;
    std::string path;
};

class Router : public IMiddleware {
public:
    Router(const std::string &path) : path(path) {

    }

    void use(const IMiddleware &newMiddleware) {
        middleware.push_back(&newMiddleware);
    }

    Route &route(std::string path = "/") {
        routes.push_back(path);
        return routes.back();
    }

    bool pathMatches(const std::string &urlPath) const {
        size_t pathPos = urlPath.find(path.c_str(), 0, path.size());
        return pathPos != std::string::npos;
    }

    virtual void handle(HttpParser::HttpRequest &req, HttpParser::HttpResponse &res) const {
        std::cout << "Handle: " << path << " " << req.path << std::endl;

        if (!pathMatches(req.path)) {
            std::cout << "Doesn't match";
            return;
        }

        for (auto &middleware : this->middleware) {
            middleware->handle(req, res);
        }

        for (const Route &route : routes) {
            if (res.status > 0) {
                break;
            }
            if (route.pathMatches(req.path.substr(path.size(), req.path.size() - path.size()))) {
                std::cout << "Path Matches " << path << " " << route.path;

                route.handle(req, res);
                return;
            }
        }
    };

    std::vector<const IMiddleware *> middleware;
    std::string path;
    std::vector<Route> routes;
};


int main() {
    Router router("/api");

    router.use(Logger());

    router.route().get([](const HttpParser::HttpRequest &req, HttpParser::HttpResponse &res) {
        res.status = 200;
        res.body = "Hello World";
    });

    Router jobsRouter("/jobs");
    Route r = jobsRouter.route();
    /*r.get([](const HttpParser::HttpRequest &req, HttpParser::HttpResponse &res) {
        res.status = 200;
        res.body = "Jobs";
    });*/
    r.put([](const HttpParser::HttpRequest &req, HttpParser::HttpResponse &res) {
        std::cout << "Put handler";

        res.status = 200;
        res.body = "Jobs";
    });

    router.use(jobsRouter);

    Router jobRouter("/");
    jobRouter.route().get([](const HttpParser::HttpRequest &req, HttpParser::HttpResponse &res) {
        size_t lastSlashPos = req.path.find_last_of("/");
        std::string id = req.path.substr(lastSlashPos + 1, req.path.size());

        res.status = 200;
        res.body = "Job: " + id;
    });
    jobsRouter.use(jobRouter);

    Server s(8000);
    s.Use(&router);
    s.Run();

    return 0;
}