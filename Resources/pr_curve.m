function [p_i, r_i] = pr_curve (top, rel, plot_style)
  p_i = []
  r_i = []
  rc = 0
  for i=1:length(top)
    if (top(i) == 1)
      rc += 1
    endif
    p_i = [p_i, rc ./i]
    r_i = [r_i, rc ./rel]
  endfor

  plot(r_i, p_i, plot_style, "linewidth", 2)
  hold on
endfunction