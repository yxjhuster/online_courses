function X = Nonlinear_Triangulation(K, C1, R1, C2, R2, C3, R3, x1, x2, x3, X0)
%% Nonlinear_Triangulation
% Refining the poses of the cameras to get a better estimate of the points
% 3D position
% Inputs: 
%     K - size (3 x 3) camera calibration (intrinsics) matrix
%     x
% Outputs: 
%     X - size (N x 3) matrix of refined point 3D locations 
N = size(X0,1);
X = zeros(N,3);
for i = 1:N
    re = Single_Point_Nonlinear_Triangulation(K, C1, R1, C2, R2, C3, R3, x1(i,:), x2(i,:), x3(i,:), X0(i,:)');
    re2 = Single_Point_Nonlinear_Triangulation(K, C1, R1, C2, R2, C3, R3, x1(i,:), x2(i,:), x3(i,:), re);
    re3 = Single_Point_Nonlinear_Triangulation(K, C1, R1, C2, R2, C3, R3, x1(i,:), x2(i,:), x3(i,:), re2);
    X(i,:) = re3';
end
end

function X = Single_Point_Nonlinear_Triangulation(K, C1, R1, C2, R2, C3, R3, x1, x2, x3, X0)
b = [x1(1), x1(2), x2(1), x2(2), x3(1), x3(2)]';
X1 = K * R1 * (X0 - C1);
X2 = K * R2 * (X0 - C2);
X3 = K * R3 * (X0 - C3);
f = [X1(1:2) / X1(3); X2(1:2) / X2(3); X3(1:2) / X3(3)];
J = Jacobian_Triangulation(K, C1, R1, C2, R2, C3, R3, X0);
X = X0 + (J' * J) \ (J' * (b - f));
end

function J = Jacobian_Triangulation(K, C1, R1, C2, R2, C3, R3, X0)
df1dX = dfdX(C1, R1, K, X0);
df2dX = dfdX(C2, R2, K, X0);
df3dX = dfdX(C3, R3, K, X0);
J = [df1dX; df2dX; df3dX];
end

function dd = dfdX(C, R ,K ,X)
f = K(1,1);
px = K(1,3);
py = K(2,3);

dudX = [f*R(1,1)+px*R(3,1) f*R(1,2)+px*R(3,2) f*R(1,3)+px*R(3,3)];
dvdX = [f*R(2,1)+py*R(3,1) f*R(2,2)+py*R(3,2) f*R(2,3)+py*R(3,3)];
dwdX = R(3,:);

X = K * R * (X - C);
u = X(1);
v = X(2);
w = X(3);

dd = [(w * dudX - u * dwdX)/ w^2; (w * dvdX - v * dwdX)/ w^2];
end