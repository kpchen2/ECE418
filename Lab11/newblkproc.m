% Created by Prakash Ishwar on May 1998 at the University of Illinois at Urbana-Champaign
%   NEWBLKPROC : Process an image in blocks.
%
%   Syntax :
%
%   [b,B] = NEWBLKPROC(A,[M N],'fun') processes the image A by
%   applying the function 'fun' to each distinct M-by-N block of
%   A.  The results are assembled to create b.  The function 'fun'
%   should operate on an M-by-N block, x, and return a matrix X :
%   X from each block is assembled to create b.
%
%   [X,Y] = fun(x); Y is the same size as B and
%    B = sum of Y of each block. i.e B = Y(block1) + Y(block2) + ...
%
%
%   EXAMPLE 1 :
%
%   energy.m is a matlab file containing the function "energy(x)"
%
%   function [X,Y] = energy(x)
%
%   X = x;
%   Y = (x.*x)/S;  % S = Total number of blocks of size 8X8 in the image
%   return;
%
%   the command :
%
%   [dummyimage avg_blk_eng_mtx] = newblkproc(image,[8,8],'energy');
%
%   returns the average energy of an 8X8 block of the the image : "image" in
%   the 8X8 matrix : avg_blk_eng_mtx. dummyimage is exactly the same as "image"
%   in this example
%
%   EXAMPLE 2 :
% 
%   blockmean.m is a matlab file containing the function "blockmean(x)"
%
%   function [X,Y] = blockmean(x)
%
%   X = x;
%   Y = x/S; % S = total number of blocks of size 8X8 in image
%   return;
%
%   the command : 
%
%   [dummyimage mean_block_energy] = newblkproc(image,[8,8],'blockmean');
%
%   returns the mean block value of an 8X8 block of the image : "image" 
%   in the 8X8 matrix : mean_block_energy. dummyimage is exactly the same
%   as "iamge" in this example.
%
%   ALSO SEE HELP ON BLKPROC

function [b,B] = newblkproc(a,block,border,P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10)

error(nargchk(3,14,nargin));

if nargin==3,
  FUN = border;
  border = [0 0];
  if ~any(FUN<48), fcall = [FUN,'(x)']; else fcall = FUN; end
else
  if isstr(P0), 
    FUN = P0; 
    % Form call string.
    params = [];
    for n=5:nargin
      params = [params,',P',int2str(n-4)];
    end
    if ~any(FUN<48), fcall = [FUN,'(x',params,')']; else fcall = FUN; end
  else
    FUN = border;
    border = [0 0];
    % Form call string and shift parameters
    params = [];
    for n=4:nargin
      params = [params,',P',int2str(n-3)];
      eval(['P',int2str(nargin-n+1),'=P',int2str(nargin-n),';']);
    end
    if ~any(FUN<48), fcall = [FUN,'(x',params,')']; else fcall = FUN; end
  end
end

% Expand A: Add border, pad if size(a) is not divisible by block.
[ma,na] = size(a);
mpad = rem(ma,block(1)); if mpad>0, mpad = block(1)-mpad; end
npad = rem(na,block(2)); if npad>0, npad = block(2)-npad; end
if isind(a),
  aa = ones(ma+mpad+2*border(1),na+npad+2*border(2));
else
  aa = zeros(ma+mpad+2*border(1),na+npad+2*border(2));
end
aa(border(1)+(1:ma),border(2)+(1:na)) = a;

%
% Process each block in turn.
%
m = block(1) + 2*border(1);
n = block(2) + 2*border(2);
mblocks = (ma+mpad)/block(1);
nblocks = (na+npad)/block(2);
b = zeros(ma+mpad,na+npad);
arows = 1:m; acols = 1:n;
brows = 1:block(1); bcols = 1:block(2);
xrows = brows + border(1); xcols = bcols + border(2);
mb = block(1); nb = block(2);
B = 0;
for i=0:mblocks-1,
  for j=0:nblocks-1,
    x = aa(i*mb+arows,j*nb+acols);
    [c,temp] = eval(fcall);
    B = temp + B;
    if all(size(c)==size(x)),
      b(i*mb+brows,j*nb+bcols) = c(xrows,xcols);
    elseif all(size(c)==size(x)-2*border),
      b(i*mb+brows,j*nb+bcols) = c;
    else
      error('Block returned by FUN is the wrong size.');
    end
  end
end
b = b(1:ma,1:na);



