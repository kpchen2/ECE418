% Created by Prakash Ishwar on May 1998 at the University of Illinois at Urbana-Champaign

function [X,Y] = covar(x,mu)

X = x;
Y = (x(:) - mu(:))*(x(:)-mu(:))';
S = (512*512)/(8*8);
Y = Y/S;
return;
