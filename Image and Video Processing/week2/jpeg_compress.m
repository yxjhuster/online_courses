function [comp_image_Y,comp_image_U,comp_image_V] = jpeg_compress(orig_image)
RGB=orig_image;
R=RGB(:,:,1);
G=RGB(:,:,2);
B=RGB(:,:,3); 
Y=0.299*double(R)+0.587*double(G) +0.114*double(B);
U=-0.169*double(R)-0.3316*double(G)+0.5*double(B);
V=0.5*double(R)-0.4186*double(G)-0.0813*double(B);

fun = @(block_struct) dct2(block_struct.data(:,:));
BY=blockproc(Y,[8 8],fun); 
BU=blockproc(U,[8 8],fun); 
BV=blockproc(V,[8 8],fun); 
a=[
16 11 10 16 24 40 51 61;
12 12 14 19 26 58 60 55;
14 13 16 24 40 57 69 55;
14 17 22 29 51 87 80 62;
18 22 37 56 68 109 103 77; 
24 35 55 64 81 104 113 92;                      
49  64 78 87 103 121 120 101;                   
72 92 95 98 112 100 103 99;
];
b=[17 18 24 47 99 99 99 99; 
18 21 26 66 99 99 99 99; 
24 26 56 99 99 99 99 99; 
47 66 99 99 99 99 99 99; 
99 99 99 99 99 99 99 99; 
99 99 99 99 99 99 99 99; 
99 99 99 99 99  99 99 99; 
99 99 99 99 99 99 99 99;];
BY2=blkproc(BY,[8 8],'round(x./P1)',a); 
BU2=blkproc(BU,[8 8],'round(x./ P1)',b); 
BV2=blkproc(BV,[8 8],'round(x./P1)',b);
comp_image_Y=img2jpg(BY2,1);        
comp_image_U=img2jpg(BU2,2);                    
comp_image_V=img2jpg(BV2,3);
end


function [ y ] = img2jpg( x,flag )
[xm, xn] = size(x);
order = [1 9  2  3  10 17 25 18 11 4  5  12 19 26 33  ...
    41 34 27 20 13 6  7  14 21 28 35 42 49 57 50  ...
    43 36 29 22 15 8  16 23 30 37 44 51 58 59 52  ...
    45 38 31 24 32 39 46 53 60 61 54 47 40 48 55  ...
    62 63 56 64];

y = im2col(x, [8 8], 'distinct');
xb = size(y, 2);
y = y(order, :);

eob = max(y(:)) + 1; 
r = zeros(numel(y) + size(y, 2), 1);
count = 0;
for j = 1:xb
    i = max(find(y(:, j)));
    if isempty(i)                   
        i = 0;
    end
    p = count + 1;
    q = p + i;
    r(p:q) = [y(1:i, j); eob]; 
    count = count + i + 1;
end

r((count + 1):end) = [];
[r1,r2]=size(r);
y           = struct;
y.realsize = r1;
y.size      = uint16([xm xn]);
y.numblocks = uint16(xb);
y.r   = r;
y.flag = flag;

end