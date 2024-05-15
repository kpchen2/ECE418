% Created by Prakash Ishwar on May 1998 at the University of Illinois at Urbana-Champaign

clear;clc;

image=imread('lena.raw');
image = double(image);

block_size = 8*8;
block_length = fix(sqrt(block_size));
coef_number = 10;

[dummy mu] = newblkproc(image,[block_length block_length],'blockmean');
[dummy Rx] = newblkproc(image,[block_length block_length],'covar',mu);
[KLT D] = eig(Rx);
KLT = KLT';
Timage = blkproc(image,[block_length block_length],'KLtransform',KLT);
[dummy avgenergy] = newblkproc(Timage,[block_length,block_length],'avgblkenergy');
[sorted index] = sort(avgenergy(:));
figure; imagesc(avgenergy)
colorbar
mask = zeros(block_size,1);
nstart = block_size - coef_number + 1;
mask(index(nstart:block_size))=1;
mask = reshape(mask,block_length,block_length);
cmprss = blkproc(Timage,[block_length block_length],'applymask',mask);
iKLT = KLT';
uncmpress = blkproc(cmprss,[block_length block_length],'invKLT',iKLT);
diff = image - uncmpress;
mse = norm(diff,'fro');
mse = (mse*mse)/(512*512)
psnr = 10*log10(255^2/mse)
figure;imshow(uncmpress,[0 255]);
figure; imagesc(mask)
