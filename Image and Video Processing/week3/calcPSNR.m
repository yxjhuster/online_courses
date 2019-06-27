function [imgPSNR] = calcPSNR(imgSrc, imgDst, bitWidth)
    if(size(imgSrc,3) == 1)
        imgMSE = sum(sum((double(imgDst) - double(imgSrc)).^2)) / (size(imgSrc,1) * size(imgSrc,2));
        imgPSNR = 10 * log10((2^bitWidth-1)^2 / imgMSE);
    else
        imgSrcGray = rgb2ycbcr(imgSrc);
        imgDstGray = rgb2ycbcr(imgDst);
        imgMSE = sum(sum((double(imgDstGray(:,:,1)) - double(imgSrcGray(:,:,1))).^2)) / (size(imgSrc,1) * size(imgSrc,2));
        imgPSNR = 10 * log10((2^bitWidth-1)^2 / imgMSE);
end