function [p_irel, r_irel] = pr_curve_orel(top, rel, plot_style)
  p_irel = []
  r_irel = []
  rc = 0
  for i=1:length(top)
    if (top(i) == 1)
      rc += 1
      p_irel = [p_irel, rc ./i]
      r_irel = [r_irel, rc ./rel]
    endif    
  endfor

  plot(r_irel, p_irel, plot_style, "linewidth", 2)
  hold on
endfunction