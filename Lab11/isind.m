% Bowen Cheng
% University of Illinois
% 2016
% isind(A) returns true if A is a matrix of index
function bool = isind(A)
    bool = isinteger(A) && min(min((A >= 1)));
end