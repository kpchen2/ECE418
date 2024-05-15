clear;clc;

% load lena.raw
fid = fopen('lena.raw', 'r');
lena = fread(fid, [512, 512]);
lena = lena' / 255;

% generate noisy images
lena_g = imnoise(lena, 'gaussian');
lena_s = imnoise(lena, 'salt & pepper');

% create linear filters
h_gauss1 = fspecial ('gaussian', 5, 0.25);
h_gauss2 = fspecial ('gaussian', 5, 0.5);
h_gauss3 = fspecial ('gaussian', 5, 1.0);
h_gauss4 = fspecial ('gaussian', 10, 0.25);
h_gauss5 = fspecial ('gaussian', 10, 0.5);
h_gauss6 = fspecial ('gaussian', 10, 1.0);
h_log1 = fspecial ('log', 5, 0.5);
h_log2 = fspecial ('log', 5, 1.0);
h_log3 = fspecial ('log', 10, 0.5);
h_log4 = fspecial ('log', 10, 1.0);

% apply filters
lena_g_smoothed1 = filter2 (h_log1, lena_g);
lena_g_smoothed2 = filter2 (h_log2, lena_g);
lena_g_smoothed3 = filter2 (h_log3, lena_g);
lena_g_smoothed4 = filter2 (h_log4, lena_g);
% lena_s_smoothed = filter2 (h_gauss, lena_s);
% lena_g_logged = filter2 (h_log, lena_g);
% lena_s_logged = filter2 (h_log, lena_s);

lena_s_median1 = medfilt2 (lena_g, [1 1]);
lena_s_median2 = medfilt2 (lena_g, [3 3]);
lena_s_median3 = medfilt2 (lena_g, [5 5]);
lena_s_median4 = medfilt2 (lena_g, [7 7]);

lena_s_median = lena;
subplot(2, 3, 1);
imshow(lena_s_median);

for i=1:10
    lena_s_median = medfilt2 (lena_s_median, [3 3]);
end

subplot(2, 3, 2);
imshow(lena_s_median);

for i=1:10
    lena_s_median = medfilt2 (lena_s_median, [3 3]);
end

subplot(2, 3, 3);
imshow(lena_s_median);

for i=1:10
    lena_s_median = medfilt2 (lena_s_median, [3 3]);
end

subplot(2, 3, 4);
imshow(lena_s_median);

for i=1:10
    lena_s_median = medfilt2 (lena_s_median, [3 3]);
end

subplot(2, 3, 5);
imshow(lena_s_median);

for i=1:10
    lena_s_median = medfilt2 (lena_s_median, [3 3]);
end

subplot(2, 3, 6);
imshow(lena_s_median);