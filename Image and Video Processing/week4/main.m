clc;clear;close all;tic;
imgSrc = rgb2gray(imread('lena.tiff'));
[h, c] = size(imgSrc);
sigma = 30;
imgRandNoise = imgSrc + uint8(sigma * randn(size(imgSrc)));
imgSaltPepper = imnoise(imgSrc,'salt & pepper', 0.02);
imgWiener1 = wiener2(imgRandNoise, [6,6]);
imgWiener2 = wiener2(imgSaltPepper, [6,6]);
figure;
subplot(2,3,1), imshow(imgSrc), title('original');
subplot(2,3,2), imshow(imgRandNoise), title('noisyImage');
subplot(2,3,3), imshow(imgSaltPepper),title('salt & pepper');
subplot(2,3,4), imshow(imgWiener1), title('Wiener & Gaussian');
subplot(2,3,5), imshow(imgWiener2),title('Wiener & SP');

imgPad = padarray(imgSrc,[128,128]);
imgCollect = zeros(h * 1.5,c * 1.5,10);
for i = 1:10
    rotation = rand(1) * pi;
    sigma = rand(1) * 0.2;
    imgNoise = imrotate(imnoise(imgSrc, 'gaussian', sigma), rotation);
    [h1,c1] = size(imgNoise);
    imgNoise = padarray(imgNoise, [floor((768 - h1)/2) floor((768 - c1)/2)], 0,'post');
    imgNoise = padarray(imgNoise, [ceil((768 - h1)/2) ceil((768 - c1)/2)], 0,'pre');
    
    imgCollect(:,:,i) = imgNoise;
end

[optimizer, metric] = imregconfig('multimodal')
optimizer.InitialRadius = 0.009;
optimizer.Epsilon = 1.5e-4;
optimizer.GrowthFactor = 1.01;
optimizer.MaximumIterations = 300;

moving_reg = imregister(imgCollect(:,:,1), imgSrc,'affine', optimizer, metric);
figure
imshowpair(imgSrc, moving_reg)