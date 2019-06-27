function averaged = averageImg(img)
% average the image representation, input should be double type
m = 1/9 * ones(3);
averaged = conv2(img,m, 'same');
end