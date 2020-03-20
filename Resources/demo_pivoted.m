vd = 0:1:20
piv = 10
alpha = 0.6
plot(vd, vd, "k.-", "linewidth", 2)
hold on
plot(vd, alpha * vd + (1 - alpha) * piv, "g.-", "linewidth", 2)
xlabel("|vector(d)|")
ylabel("pivoted norm")