% Created by Prakash Ishwar on May 1998 at the University of Illinois at Urbana-Champaign

function Y = KLtransform(x,KLT)

Y = KLT*x(:);
Y = reshape(Y,8,8);
return;
