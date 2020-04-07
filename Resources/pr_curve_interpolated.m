function p_interp = pr_curve_interpolated(p_i, r_i, r_norm, plot_style)
  p_interp = []
  for r = r_norm
    p_interp = [p_interp, pr_interp(p_i, r_i, r)]
  endfor
  plot(r_norm, p_interp, plot_style, "linewidth", 2)
  hold on
endfunction