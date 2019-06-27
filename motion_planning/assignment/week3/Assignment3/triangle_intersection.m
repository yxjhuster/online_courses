function flag = triangle_intersection(P1, P2)
% triangle_test : returns true if the triangles overlap and false otherwise

%%% All of your code should be between the two lines of stars.
% *******************************************************************
flag=true;
flag1=checkTriangle(P1,P2);
flag2=checkTriangle(P2,P1);

if flag1 || flag2
    flag=false;
end


% *******************************************************************
end

function flag=checkTriangle(A,B)

A = [A; A(1,:)];

flag=false;

    for j = 2:4
               
        %We obtain the vector that defines the edge
        dx = A(j,1) - A(j-1,1);
        dy = A(j,2) - A(j-1,2); 

        %And an origin point for the vector
        x_o = A(j-1,1);
        y_o = A(j-1,2);
        
        if(j == 2)
            ownSide = sign(-dy * (A(3,1) - x_o) + dx * (A(3,2) - y_o));
        elseif(j == 3)
            ownSide = sign(-dy * (A(1,1) - x_o) + dx * (A(1,2) - y_o));
        elseif(j == 4)
            ownSide = sign(-dy * (A(2,1) - x_o) + dx * (A(2,2) - y_o));
        end
        
        otherSide = zeros(3,1);
        
        for k=1:3
            otherSide(k) = sign(-dy * (B(k,1) - x_o) + dx * (B(k,2) - y_o)); 
        end
        
        if ( ownSide < 0 && min(otherSide) > 0) || ( ownSide > 0 && max(otherSide) < 0)
            flag = true;
            break;
        end
    end


end