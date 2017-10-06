package org.Demo;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

public class ReadJSONExample {
    public static void main(String[] args) {
        //JSON parser object to parse read file
        JSONParser jsonParser = new JSONParser();
        try (FileReader reader = new FileReader("ir1.json"))
        {
            JSONObject root = (JSONObject) jsonParser.parse(reader);
            JSONArray collection = (JSONArray) root.get("collection");
            collection.forEach(q -> parseQueryDetailObject((JSONObject) q));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ParseException e) {
            e.printStackTrace();
        }
    }

    private static void parseQueryDetailObject(JSONObject queryDetail)
    {
        String query = (String)queryDetail.get("query");
        String description = (String)queryDetail.get("description");
        System.out.printf("query: %s\ndescription:%s\nsites:\n", query, description);
        JSONArray sites = (JSONArray)queryDetail.get("sites");
        for (Object obj: sites) {
            JSONObject siteDetail = (JSONObject)obj;
            String url = (String) siteDetail.get("url");
            String title = (String) siteDetail.get("title");
            String content = (String) siteDetail.get("content");
            boolean relevance = ((Long)siteDetail.get("relevance") == 1);
            System.out.printf("\turl = %s\n\ttitle = %s\n\tcontent = %s\n\trelevance = %s\n", url, title, content, relevance);
        }
    }
}
