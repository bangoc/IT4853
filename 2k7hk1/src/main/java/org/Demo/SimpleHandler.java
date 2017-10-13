package org.Demo;

import org.apache.lucene.queryparser.classic.ParseException;
import org.eclipse.jetty.server.Request;
import org.eclipse.jetty.server.handler.AbstractHandler;
import org.json.simple.JSONObject;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class SimpleHandler extends AbstractHandler
{
    private SimpleSearcher searcher = new SimpleSearcher();

    public SimpleHandler() throws IOException {
    }

    public void handle(String target, Request baseRequest, HttpServletRequest request, HttpServletResponse response)
            throws IOException, ServletException
    {
        if (!target.equalsIgnoreCase("/search"))
            return;

        try {
            JSONObject result = searcher.search(baseRequest.getParameter("q"));
            response.setContentType("text/html;charset=utf-8");
            response.setStatus(HttpServletResponse.SC_OK);
            baseRequest.setHandled(true);
            response.getWriter().println(result.toJSONString());

        } catch (ParseException e) {
            e.printStackTrace();
        }
    }
}