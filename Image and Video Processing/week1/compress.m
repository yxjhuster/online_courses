function compressed = compress(img)
% compress image to binary representation, input should be double type
compressed = floor(img / 255) * 255;
end