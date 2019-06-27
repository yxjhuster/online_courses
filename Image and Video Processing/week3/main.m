clc;clear;close all;tic;
imgSrc = rgb2gray(imread('lena.tiff'));
sigma = 15;
imgRandNoise = imgSrc + uint8(sigma * randn(size(imgSrc)));
h = sigma;
imgDst = NLmeansfilter(double(imgRandNoise), 10, 3, h);
imgDst = uint8(imgDst);
figure;
subplot(2,2,1), imshow(imgSrc), title('original');
subplot(2,2,2), imshow(imgRandNoise), title('noisyImage');
subplot(2,2,3), imshow(imgDst), title('denoising');
subplot(2,2,4), imshow(imgRandNoise - imgDst), title('noisy');
 
filterGaussian = fspecial('gaussian');      %3x3 gaussian filter
filterAverage = fspecial('average');        %3x3 average filter
imgGaussian = imfilter(imgRandNoise, filterGaussian, 'replicate');
imgAverage = imfilter(imgRandNoise, filterAverage, 'replicate');

figure;
subplot(2,2,1),imshow(imgSrc);
subplot(2,2,2),imshow(imgDst),title(['PSNR = ', num2str(calcPSNR(imgSrc, imgDst, 8))]);
subplot(2,2,3),imshow(imgGaussian),title(['PSNR = ', num2str(calcPSNR(imgSrc, imgGaussian, 8))]);
subplot(2,2,4),imshow(imgAverage),title(['PSNR = ', num2str(calcPSNR(imgSrc, imgAverage, 8))]);
 
toc;