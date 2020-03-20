w_tf = 0:0.1:10
w_df = 0:0.1:10
[xx, yy] = meshgrid(w_tf, w_df)
w_tfidf = xx .* yy
mesh(w_tf, w_df, w_tfidf)
xlabel("w_tf")
ylabel("w_df")
zlabel("w_tfidf")