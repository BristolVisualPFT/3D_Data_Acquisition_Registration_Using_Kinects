%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%                        University of Bristol                        %%%
%%%%%                   Computer Science Department                   %%%%%
%%%=====================================================================%%%
%%%                 This is an open source code for:                    %%%
%%%  "3D Data Acquisition and Registration using Two Opposing Kinects"  %%%
%%%     V. Soleimani, M. Mirmehdi, D. Damen, S. Hannuna, M. Camplani    %%%
%%%        International Conference on 3D Vision, Stanford, 2016        %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%
function [registeredRGB, undistorted] = register_depth2color(rgb_data, depth_data, distort_map, depth_to_color_map_x, depth_to_color_map_yi, color_params, depth_params, filter_params, enable_filter)
size_depth = 512 * 424;
size_color = 1920 * 1080;
undistorted(424,512)=0;
registered(424,512)=0;
undistorted_data = reshape(undistorted',1,size_depth);
registered_data_R = reshape(registered',1,size_depth);
registered_data_G = reshape(registered',1,size_depth);
registered_data_B = reshape(registered',1,size_depth);
depth_data = reshape(double(depth_data'),1,size_depth);
rgb_data_R = reshape(uint16(rgb_data(:,:,1)'),1,size_color);
rgb_data_G = reshape(uint16(rgb_data(:,:,2)'),1,size_color);
rgb_data_B = reshape(uint16(rgb_data(:,:,3)'),1,size_color);

map_dist = distort_map;
map_x = depth_to_color_map_x;
map_yi = depth_to_color_map_yi;
color = color_params;
filter_p = filter_params;
color_cx = color.cx + 0.5;

size_filter_map = size_color + 1920 * filter_p.filter_height_half * 2;
offset_filter_map = 1920 * filter_p.filter_height_half;

depth_to_c_off(size_depth) = 0;

filter_map = Inf(1,size_filter_map);

for i = 1: size_depth
    index = map_dist(i);
    
    if(index < 1)
        depth_to_c_off(i) = -1;
        undistorted_data(i) = 0;
        continue;
    end
    
    z = depth_data(index);
    undistorted_data(i) = z;
    
    if(z <= 0)
        depth_to_c_off(i) = -1;
        continue;
    end
    
    rx = (map_x(i) + (color.shift_m / z)) * color.fx + color_cx;
    cx = int32(floor(rx));
    cy = int32(map_yi(i));
    c_off = cx + (cy-1) * 1920;
    
    if(c_off < 1 || c_off > size_color)
        depth_to_c_off(i) = -1;
        continue;
    end
    
    depth_to_c_off(i) = c_off;
    
    if enable_filter==1
        yi = int32((cy - filter_p.filter_height_half -1) * 1920 + cx - filter_p.filter_width_half);
        for r = -filter_p.filter_height_half: filter_p.filter_height_half
            it = offset_filter_map + yi;
            for c = -filter_p.filter_width_half: filter_p.filter_width_half
                if(z < filter_map(it))
                    filter_map(it) = z;
                end
                it = it + 1;
            end
            yi = yi + 1920;
        end
    end
end

if(enable_filter==1)
    for i = 1:size_depth
        c_off = int32(depth_to_c_off(i));
        
        if(c_off < 1)
            registered_data_R(i) = 0;
            registered_data_G(i) = 0;
            registered_data_B(i) = 0;            
            continue;
        end
        
        min_z = filter_map(offset_filter_map + c_off);
        z = undistorted_data(i);
        
        
        tmp_z = (z - min_z)/z;
        
        if tmp_z > filter_p.filter_tolerance
            registered_data_R(i) = 0;
            registered_data_G(i) = 0;
            registered_data_B(i) = 0;
        else
            registered_data_R(i) = rgb_data_R(c_off);
            registered_data_G(i) = rgb_data_G(c_off);
            registered_data_B(i) = rgb_data_B(c_off);
        end
        
    end
    
else
    for i = 1 : size_depth
        c_off = depth_to_c_off(i);
        
        if (c_off < 1)
            registered_data_R(i) = 0;
            registered_data_G(i) = 0;
            registered_data_B(i) = 0;
        else
            registered_data_R(i) = rgb_data_R(c_off);
            registered_data_G(i) = rgb_data_G(c_off);
            registered_data_B(i) = rgb_data_B(c_off);
        end
    end
end
undistorted = undistorted_data;
registeredRGB = [registered_data_R', registered_data_G', registered_data_B'];
end
%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%                        University of Bristol                        %%%
%%%%%                   Computer Science Department                   %%%%%
%%%=====================================================================%%%
%%%                 This is an open source code for:                    %%%
%%%  "3D Data Acquisition and Registration using Two Opposing Kinects"  %%%
%%%     V. Soleimani, M. Mirmehdi, D. Damen, S. Hannuna, M. Camplani    %%%
%%%        International Conference on 3D Vision, Stanford, 2016        %%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%