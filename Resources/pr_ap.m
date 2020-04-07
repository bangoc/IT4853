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

[p_irel1, r_irel1] = pr_curve_orel(top1, rel1, "rd-;q1_rel;")
ap1 = sum(p_irel1) / rel1

rel2 = 17
top2 = [1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1]
[p_i2, r_i2] = pr_curve(top2, rel2, "g.-;q2;")

[p_irel2, r_irel2] = pr_curve_orel(top2, rel2, "rd-;q2_rel;")
ap2 = sum(p_irel2) / rel2

map = (ap1 + ap2) / 2