% Created by Prakash Ishwar on May 1998 at the University of Illinois at Urbana-Champaign

function [X,Y] = avgblkenergy(x)

X = x;
S = (512*512)/(8*8);
Y = (x.*x)/S;
return;
