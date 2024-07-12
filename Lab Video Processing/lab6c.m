clear;clc;

% Reading Tank images
for j=1:9
 s=sprintf('tank_0%d.raw',j);
 fid=fopen(s,'r');
 tank(:,:,j)=(fread(fid,[486,486],'uchar'))';
 fclose(fid);
end

% Pyramid decomposition

%*******************************************************************************
% Your code goes in here.
% Generate the coded and diff images and display them 
% after appropriate intensity rescaling
%*******************************************************************************

i = 1;
k = 1;
for j=1:9
    if mod(j,2) == 1
        tank1(:,:,i) = tank(:,:,j);
        i = i+1;
    else
        diff_tank1(:,:,k) = tank(:,:,j)-(tank(:,:,j-1)+tank(:,:,j+1))/2;
        X = diff_tank1(:,:,k);
        colormap gray;
        subplot(4,1,k);
        imagesc(X);
        k = k+1;
    end
end

i = 1;
k = 1;
for j=1:5
    if mod(j,2) == 1
        tank2(:,:,i) = tank1(:,:,j);
        i = i+1;
    else
        diff_tank2(:,:,k) = tank1(:,:,j)-(tank1(:,:,j-1)+tank1(:,:,j+1))/2;
        X = diff_tank2(:,:,k);
        colormap gray;
        subplot(2,1,k);
        imagesc(X);
        k = k+1;
    end
end

% Conceptually, if images have to be transmitted, the following frames will be sent:
% coded(:,:,k); k=1,5,9 and diff(:,:,k); k=2,3,4,6,7,8.

%*******************************************************************************
% Your code goes in here
% Getting back the data (decoding)
% recon=coded+diff;
% Check for Perfect Reconstruction by computing MSE:
%*******************************************************************************

i = 1;
for j=1:5
    if mod(j,2) == 1
        re_tank1(:,:,j) = tank2(:,:,i);
        i = i+1;
    else
        re_tank1(:,:,j) = diff_tank2(:,:,i-1) + (tank2(:,:,i)+tank2(:,:,i-1))/2;
    end
end

i = 1;
for j=1:9
    if mod(j,2) == 1
        recon(:,:,j) = re_tank1(:,:,i);
        i = i+1;
    else
        recon(:,:,j) = diff_tank1(:,:,i-1) + (re_tank1(:,:,i)+re_tank1(:,:,i-1))/2;
    end
end

MSE=0;
for j=1:9
    MSE=MSE+norm(recon(:,:,j)-tank(:,:,j),'fro')^2;
    
    X=recon(:,:,j);
    colormap gray;
    imagesc(X);
    MM(:,j)=getframe;
end

fprintf(1,'Strike a key for movie show (subsampling by 4)...\n');
pause

% play movie at default rate of 12 fps, 4 times forwards and backwards
% colormap gray;movie(MM,-4,12);

MSE % Should be zero
