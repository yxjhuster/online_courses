function route = GradientBasedPlanner (f, start_coords, end_coords, max_its)
% GradientBasedPlanner : This function plans a path through a 2D
% environment from a start to a destination based on the gradient of the
% function f which is passed in as a 2D array. The two arguments
% start_coords and end_coords denote the coordinates of the start and end
% positions respectively in the array while max_its indicates an upper
% bound on the number of iterations that the system can use before giving
% up.
% The output, route, is an array with 2 columns and n rows where the rows
% correspond to the coordinates of the robot as it moves along the route.
% The first column corresponds to the x coordinate and the second to the y coordinate
%
% NOTE: Once the route array has been updated, pass the array as is instead of appending with zeros or NAN

[gx, gy] = gradient (-f);

%%% All of your code should be between the two lines of stars.
% *******************************************************************
iteration = 1;
cur_coords = start_coords;
tmp_route = cur_coords;
while(iteration < max_its) && (norm(cur_coords - end_coords) >= 2)
    i = round(cur_coords(2)); j = round(cur_coords(1));
    velocity_x = gx(i, j);
    velocity_y = gy(i, j);
    velocity = [velocity_x, velocity_y] / norm([velocity_x, velocity_y]);
    cur_coords = cur_coords + velocity;
    tmp_route = [tmp_route; cur_coords];
    iteration = iteration + 1;
end

if(iteration == max_its)
    route = NAN;
else
    route = double(tmp_route);
end
% *******************************************************************
end