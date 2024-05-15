% Created by Prakash Ishwar on May 1998 at the University of Illinois at Urbana-Champaign

clear;clc;

image=imread('lena.raw');
image = double(image);


Timage = blkproc(image,[8 8],'dct2');
[dummy avgenergy] = newblkproc(Timage,[8,8],'avgblkenergy');
[sorted index] = sort(avgenergy(:));
mask = zeros(64,1);
mask(index(55:64))=1;
mask = reshape(mask,8,8);
cmprss = blkproc(Timage,[8 8],'applymask',mask);
uncmpress = blkproc(cmprss,[8 8],'idct2');
diff = image - uncmpress;
mse = norm(diff,'fro');
mse = (mse*mse)/(512*512)
psnr = 10*log10(255^2/mse)
figure; imshow(uncmpress,[0 255]);

