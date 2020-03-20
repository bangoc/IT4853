N = 20
df = 1:1:N
plot(df, df, "r", "linewidth", 1)
hold on
plot(df, N./df, "k.-", "linewidth", 2)
hold on
plot(df, log(N./df), "g+-", "linewidth", 2)