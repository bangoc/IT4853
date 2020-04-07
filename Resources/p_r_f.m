res_q1 = [5, 1, 3, 6, 10, 8, 9, 11, 22, 35, 36, 50]
rel_q1 = [3, 9, 20, 22, 35, 50, 60]

top_q1 = check_relevance(res_q1, rel_q1)
P_q1 = sum(top_q1)/length(res_q1)
R_q1 = sum(top_q1)/length(rel_q1)

res_q2 = [2, 5, 6, 8, 11, 22, 23, 28, 33, 1, 9, 35, 40, 88]
rel_q2 = [2, 10, 15, 23, 30, 39, 40, 60]
top_q2 = check_relevance(res_q2, rel_q2)
P_q2 = sum(top_q2)/length(res_q2)
R_q2 = sum(top_q2)/length(rel_q2)

b2 = 1.0
F1_q1 = 2 * P_q1 * R_q1 / (P_q1 + R_q1)
F1_q2 = 2 * P_q2 * R_q2 / (P_q2 + R_q2)

F1_avg = (F1_q1 + F1_q2) / 2  % macro