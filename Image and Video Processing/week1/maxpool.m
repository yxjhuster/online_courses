function maxpooled = maxpool(img, stride)
% do maxpooling for the image
fun = @(block_struct) max(block_struct.data(:));
maxpooled = blockproc (img, stride, fun);
end