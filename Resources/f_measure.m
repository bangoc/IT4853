figure(1, 'position',[0,0,1280,800]);

r = 0.7
p = 0:0.1:1.0
plot(p, min(p, r), "kd--;min(P, R);", "linewidth", 2)
legend("location", "northwest")
title("Các phương pháp kết hợp P và R")
xlabel("P (R=0.7)")
ylabel("Đại lượng kết hợp P và R")

hold on
plot(p, max(p, r), "kd:;max(P, R);", "linewidth", 2)
hold on
plot(p, 0.8 * p + 0.2 * r, "k.-;0.8P+0.2R;", "linewidth", 2)
hold on
plot(p, 0.2 * p + 0.8 * r, "kx-;0.2P+0.8R;", "linewidth", 2)
hold on
plot(p, 2 * p * r ./ (p + r), "b+-;2pr/(p+r);", "linewidth", 2)
hold on
plot(p, 1.1 * p * r ./ (0.1*p + r), "g+--;1.1pr/(0.1p+r);", "linewidth", 2)
hold on
plot(p, 10 * p * r ./ (9*p + r), "c+--;10pr/(9p+r);", "linewidth", 2)