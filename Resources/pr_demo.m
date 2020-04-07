figure(1, 'position',[0,0,1280,800]);

plot(0:0.1:1, 0:0.1:1, "w.-", "linewidth", 1)
hold on

rel1 = 5
top1 = [1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1]
[p_i1, r_i1] = pr_curve(top1, rel1, "k+-;q1;")
title("Biểu đồ P/R")
xlabel("R")
ylabel("P")
legend("show")

top2 = [1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1]
[p_i2, r_i2] = pr_curve(top2, rel2, "g.-;q2;")

r_norm = 0:0.1:1
p_interp1 = pr_curve_interpolated(p_i1, r_i1, r_norm, "b+-;q1_interp;")
p_interp2 = pr_curve_interpolated(p_i2, r_i2, r_norm, "b.-;q2_interp;")
p_interp_avg = (p_interp1 + p_interp2) / 2

plot(r_norm, p_interp_avg, "rd-;q1_q2_interp_avg;", "linewidth", 2)
hold on
