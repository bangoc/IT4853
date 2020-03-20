tf = 1:1:30
plot(tf, tf, "k.-", "linewidth", 2)
hold on
plot(tf, 1 + log(tf), "g+-", "linewidth", 2)