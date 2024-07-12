% MATLAB skeleton code for lab6b:
clear;clc;

% Read in Football Sequence and form movie M
for j=1:21
 if j<=10
  s=sprintf('fn00%d',j-1);
 else
  s=sprintf('fn0%d',j-1);
 end
 fid=fopen(s,'r');
 foot1(:,:,j)=(fread(fid,[352,240],'uchar'))';
 fclose(fid);
 colormap gray;
 X=foot1(:,:,j);
 imagesc(X);
 M(:,j)=getframe;
end

fprintf(1,'Strike a key for movie show...\n');
pause

% play movie at default rate of 12 fps, 4 times forwards and backwards
% colormap gray; movie(M,-4,12);

% Decimation and linear interpolation by 2
MSE_2=0;
for j=1:21
 if mod(j,2)~=1
  foot2(:,:,j)=(foot1(:,:,j-1)+foot1(:,:,j+1))/2;
  MSE_2=MSE_2+norm(foot1(:,:,j)-foot2(:,:,j),'fro')^2;
 else
  foot2(:,:,j)=foot1(:,:,j);
 end
 X=foot2(:,:,j);
 % subplot(3,7,j);
 colormap gray;
 imagesc(X);
 MM(:,j)=getframe;
end

fprintf(1,'Strike a key for movie show (subsampling by 2)...\n');
pause

% play movie at default rate of 12 fps, 4 times forwards and backwards
% colormap gray;movie(MM,-4,12);

% MSE for factor 2
MSE_2=MSE_2/(21*prod(size(X))) 

% Decimation and linear interpolation by 4

%******************************************************************************* 
% Your code goes in here
%******************************************************************************* 

MSE_4 = 0;
for j=1:21
    if mod(j,4)==1
        foot4(:,:,j)=foot1(:,:,j);
    elseif mod(j,4)==2
        foot4(:,:,j)=foot1(:,:,j-1)*3/4+foot1(:,:,j+3)/4;
        MSE_4=MSE_4+norm(foot1(:,:,j)-foot4(:,:,j),'fro')^2;
    elseif mod(j,4)==3
        foot4(:,:,j)=foot1(:,:,j-2)/2+foot1(:,:,j+2)/2;
        MSE_4=MSE_4+norm(foot1(:,:,j)-foot4(:,:,j),'fro')^2;
    else
        foot4(:,:,j)=foot1(:,:,j-3)/4+foot1(:,:,j+1)*3/4;
        MSE_4=MSE_4+norm(foot1(:,:,j)-foot4(:,:,j),'fro')^2;
    end
    X=foot4(:,:,j);
    subplot(3,7,j);
    colormap gray;
    imagesc(X);
    MM(:,j)=getframe;
end

fprintf(1,'Strike a key for movie show (subsampling by 4)...\n');
pause

% play movie at default rate of 12 fps, 4 times forwards and backwards
% colormap gray;movie(MM,-4,12);

% MSE for factor 4
% MSE_4=MSE_4/(21*prod(size(X))) 
