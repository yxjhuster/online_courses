function [C, R] = LinearPnP(X, x, K)
%% LinearPnP
% Getting pose from 2D-3D correspondences
% Inputs:
%     X - size (N x 3) matrix of 3D points
%     x - size (N x 2) matrix of 2D points whose rows correspond with X
%     K - size (3 x 3) camera calibration (intrinsics) matrix
% Outputs:
%     C - size (3 x 1) pose transation
%     R - size (3 x 1) pose rotation
%
% IMPORTANT NOTE: While theoretically you can use the x directly when solving
% for the P = [R t] matrix then use the K matrix to correct the error, this is
% more numeically unstable, and thus it is better to calibrate the x values
% before the computation of P then extract R and t directly
[n, ~] = size(x);
x = [x, ones(n,1)];
x = (inv(K) * x')';

X = [X, ones(n, 1)];
A = [zeros(n, 4) -X  x(:,2).*X; X zeros(n, 4) -x(:,1).*X; -x(:,2).*X x(:,1).*X zeros(n, 4)];

[~,~,v] = svd(A);
P = reshape(v(:,end), [4,3])';
R=P(:,1:3); 
t=P(:,4);

[u, s, v] = svd(R);
R = u * v';

if det(R)>0
    t = t / s(1,1);
else
    R = -R;
    t = -t / s(1,1);
end
C = -1* R' * t;
end
