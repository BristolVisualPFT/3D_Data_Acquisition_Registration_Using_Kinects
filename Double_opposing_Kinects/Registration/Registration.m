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
function [distort_map, depth_to_color_map_x, depth_to_color_map_y, depth_to_color_map_yi] = Registration(filter_params, depth, color)
distort_map(512 * 424)=0;
depth_to_color_map_x(512 * 424)=0;
depth_to_color_map_y(512 * 424)=0;
depth_to_color_map_yi(512 * 424)=0;
m_counter = 1;
for y = 1:424
    for x = 1:512
        [mx,my] = distort(x,y,depth);
        ix = int32(floor(mx + 0.5));
        iy = int32(floor(my + 0.5));
        if(ix < 1 || ix >= 513 || iy < 1 || iy >= 425)
            index = -1;
        else
            index = (iy-1) * 512 + ix;
        end
        
        distort_map(m_counter) = index;
        
        [rx, ry] = depth_to_color(x, y, filter_params, depth, color);
        depth_to_color_map_x(m_counter) = rx;
        depth_to_color_map_y(m_counter) = ry;
        depth_to_color_map_yi(m_counter) = int32(floor(ry+0.5));
        m_counter = m_counter + 1;
    end
end
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