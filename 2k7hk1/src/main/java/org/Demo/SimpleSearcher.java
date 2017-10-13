package org.Demo;

import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.index.DirectoryReader;
import org.apache.lucene.index.IndexReader;
import org.apache.lucene.queryparser.classic.ParseException;
import org.apache.lucene.queryparser.classic.QueryParser;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.ScoreDoc;
import org.apache.lucene.search.TopDocs;
import org.apache.lucene.store.FSDirectory;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

import java.io.IOException;
import java.nio.file.Paths;

public class SimpleSearcher {
    public static final String index_path = "/home/bangoc/IdeaProjects/Demo/Data";
    public static final String field = "contents";
    private IndexReader reader = DirectoryReader.open(FSDirectory.open(Paths.get(index_path)));
    private IndexSearcher searcher = new IndexSearcher(reader);
    private Analyzer analyzer = new StandardAnalyzer();
    private QueryParser parser = new QueryParser(field, analyzer);
    public SimpleSearcher() throws IOException {
    }
    public JSONObject search(String query_text) throws ParseException, IOException {
        Query query = parser.parse(query_text);
        TopDocs results = searcher.search(query, 100);
        ScoreDoc[] hits = results.scoreDocs;
        JSONObject out = new JSONObject();
        JSONArray arr = new JSONArray();
        for (ScoreDoc scoreDoc: hits) {
            Document doc = searcher.doc(scoreDoc.doc);
            JSONObject obj = new JSONObject();
            obj.put("path", doc.get("path"));
            arr.add(obj);
        }
        out.put("hits", arr);
        return out;
    }
}
