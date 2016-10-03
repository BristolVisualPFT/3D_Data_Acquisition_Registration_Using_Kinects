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
function Fixed = kinect_undistort(Bad, Parms, aliased)
fx = Parms(1);
fy = Parms(2);
cx = Parms(3);
cy = Parms(4);
k1 = Parms(5);
k2 = Parms(6);
k3 = Parms(7);
p1 = Parms(8);
p2 = Parms(9);
[NumRows, NumColumns] = size(Bad);
[j, i] = meshgrid(1:NumColumns, 1:NumRows);
Xp = (j-cx)/fx;
Yp = (i-cy)/fy;
r2 = Xp.^2 + Yp.^2;
x=Xp;
y=Yp;
x = x.*(1+k1*r2 + k2*r2.^2 + k3*r2.^3) + 2*p1.*x.*y + p2*(r2 + 2*x.^2);
y = y.*(1+k1*r2 + k2*r2.^2 + k3*r2.^3) + 2*p2.*x.*y + p1*(r2 + 2*y.^2);
u = fx*x+cx;
v = fy*y+cy;
if aliased==1
    u = floor(u);
    v = floor(v);
end
Fixed = interp2(Bad, u, v);
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