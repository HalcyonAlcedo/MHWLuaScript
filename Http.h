#pragma once
#include "HttpClient.h"

namespace HttpServer {
    string GetHttpData(string url) {
		HttpClient session;
		HttpRequest req;
		req.method = "GET";
		req.url = url;
		HttpResponse res;
		int ret = session.Send(req, &res);
		string retString = "";
		if (ret != 0) {
			retString = HttpClient::strerror(ret);
		}
		else {
			retString = res.body;
		}
		return retString;
    }
}