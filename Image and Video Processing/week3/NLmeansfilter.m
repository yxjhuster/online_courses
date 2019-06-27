function [output] = NLmeansfilter(input, t, f, h)
%  input: image to be filtered
%  t: radius of search window
%  f: radius of similarity window
%  h: degree of filtering
    [m, n] = size(input);
    output=zeros(m,n);
    input2 = padarray(input,[f f],'replicate');
    kernel = fspecial('gaussian', [2*f+1 2*f+1], 1);
    hwait=waitbar(0,'计算中...'); 
    for i = 1:m
        for j = 1:n
            value = 100 * i / m;
            waitbar(i/m, hwait, sprintf('计算中:%3.2f%%',value));
            i1 = i + f;
            j1 = j + f;
            W1= input2(i1-f:i1+f , j1-f:j1+f);
            wmax = 0;
            average = 0;
            sweight = 0;
            rmin = max(i1-t,f+1);
            rmax = min(i1+t,m+f);
            smin = max(j1-t,f+1);
            smax = min(j1+t,n+f);
            for r = rmin:1:rmax
                for s = smin:1:smax
                    if(r==i1 && s==j1)
                        continue;
                    end
                    W2= input2(r-f:r+f , s-f:s+f);          %search window中的2f+1领域
                    d = sum(sum(kernel.*((W1-W2).^2)));     %两个2f+1邻域的高斯加权欧式距离
                    w = exp(-d/(h^2));                      %像素点(r-f,s-f)的权重系数Z(i)
                    if w>wmax
                        wmax = w;
                    end
                    sweight = sweight + w;                  %除了像素点(i,j)外的所有点的权值和
                    average = average + w * input2(r,s);    %除了像素点(i,j)外的所有点的加权值
                end
            end
            average = average + wmax*input2(i1,j1);         %search window的加权和
            sweight = sweight + wmax;                       %search window的权值和   
            if sweight > 0
                output(i,j) = uint8(average / sweight);
            else
                output(i,j) = input(i,j);
            end
        end
    end
    
    close(hwait);
end