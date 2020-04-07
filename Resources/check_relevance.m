function top = check_relevance(res, rel)
  top = []
  for i = res
    dq = 0
    for j = rel
      if (i == j)
        dq = 1
        break
      endif
    endfor      
    top = [top, dq]
  endfor
endfunction