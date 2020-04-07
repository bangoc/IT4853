function val = pr_interp(p_i, r_i, r)
  val = 0
  for i=1:length(p_i)
    if (r_i(i) >= r && p_i(i) > val)
      val = p_i(i)
    endif
  endfor
endfunction
