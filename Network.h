#pragma once
#include "HttpClient.h"
#include "easywsclient.hpp"
#include <assert.h>

namespace NetworkServer {
	static easywsclient::WebSocket::pointer ws = NULL;
	queue<string> MessageCache;

	void handle_message(const string& message)
	{
		MessageCache.push(message);
	}

	static void LinkWS(string link) {
		ws = easywsclient::WebSocket::from_url(link);
		assert(ws);
	}

	static void WSSendMessage(string Message) {
		ws->send(Message);
	}

	static void WSHandle() {
		if (ws != NULL and ws->getReadyState() != easywsclient::WebSocket::CLOSED) {
			ws->poll();
			ws->dispatch(handle_message);
		}
	}

	static bool WSState() {
		if (ws != NULL) {
			if (
				ws->getReadyState() == easywsclient::WebSocket::CONNECTING or
				ws->getReadyState() == easywsclient::WebSocket::OPEN
			)
				return true;
		}
		return  false;
	}
	
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