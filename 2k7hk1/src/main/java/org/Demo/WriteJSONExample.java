package org.Demo;

import java.io.FileWriter;
import java.io.IOException;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

public class WriteJSONExample
{
    public static void main( String[] args )
    {

        JSONObject root = new JSONObject();
        JSONArray collection = new JSONArray();
        JSONObject queryDetail1 = new JSONObject();
        queryDetail1.put("query", "Các giải thuật sắp xếp");
        queryDetail1.put("description", "Muốn tìm hiểu về giải thuật sắp xếp, bất kỳ trang web nào cung cấp thông tin về giải thuật sắp xếp: tổng hợp các giải thuật sắp xếp, giải thích về một giải thuật sắp cụ thể, hướng dẫn cài đặt giải thuật sắp xếp trên một ngôn ngữ lập trình đều là kết quả phù hợp.");

        JSONArray q1Sites = new JSONArray();
        JSONObject siteDetail1 = new JSONObject();
        siteDetail1.put("url", "https://vi.wikipedia.org/wiki/Thu%E1%BA%ADt_to%C3%A1n_s%E1%BA%AFp_x%E1%BA%BFp");
        siteDetail1.put("title", "Thuật toán sắp xếp – Wikipedia tiếng Việt");
        siteDetail1.put("content", "Điểm khác biệt giữa sắp xếp nhanh và sắp xếp trộn là trong sắp xếp trộn việc xác định thứ tự được xác định khi \\\"trộn\\\"");
        siteDetail1.put("relevance", 1);
        q1Sites.add(siteDetail1);
        queryDetail1.put("sites", q1Sites);
        collection.add(queryDetail1);
        root.put("collection", collection);

        //Write JSON file
        try (FileWriter file = new FileWriter("ir1.json")) {
            // file.write(root.toJSONString());
            root.writeJSONString(file);  // prefer this form
            file.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}