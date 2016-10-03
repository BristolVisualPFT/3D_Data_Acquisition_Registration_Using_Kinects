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
clc
clear all;
close all;
%% two point clouds rgbd data main path definition
data_path = 'D:\sample_rgbd_data\';
%% load Kinects depth sensor intrinsic parameters
load([data_path 'Kinect542_depth_params.mat']);
Fx_kwin542 = depth_params.fx;
Fy_kwin542 = depth_params.fy;
Px_kwin542 = depth_params.cx;
Py_kwin542 = depth_params.cy;
R2_kwin542 = depth_params.k1;
R4_kwin542	= depth_params.k2;
R6_kwin542	= depth_params.k3;
kwin_serial = mod(depth_params.device_serial,1000);
kwin542_params = [Fx_kwin542 Fy_kwin542 Px_kwin542 Py_kwin542 R2_kwin542 R4_kwin542 R6_kwin542 0 0];
clear depth_params;
load([data_path 'Kinect947_depth_params.mat']);
Fx_kxbox = depth_params.fx;
Fy_kxbox = depth_params.fy;
Px_kxbox = depth_params.cx;
Py_kxbox = depth_params.cy;
R2_kxbox = depth_params.k1;
R4_kxbox = depth_params.k2;
R6_kxbox = depth_params.k3;
kxbox_params = [Fx_kxbox Fy_kxbox Px_kxbox Py_kxbox R2_kxbox R4_kxbox R6_kxbox 0 0];
kxbox_serial = mod(depth_params.device_serial,1000);
%% read chessboards setup depth and infrared data of kwin sensor
I = imread([data_path 'setup_rgbd_data\kwin_setup_rgbd\infraRed\infraRed00100.png']);
Depth_KL_win = imread([data_path 'setup_rgbd_data\kwin_setup_rgbd\DEPTH\depth00100.png']);
%% Infrared image normalization
Id = double(I);
InfraredSourceValueMaximum = 65535;
InfraredSceneValueAverage = 0.02;
InfraredSceneStandardDeviations = 3.0;
Id = Id ./ InfraredSourceValueMaximum;
Id = Id ./ (InfraredSceneValueAverage * InfraredSceneStandardDeviations);
Id(Id > 1.0) = 1;
Id(Id < 0.01) = 0.01;
Id = Id .* 255;
Iinfra = uint16(Id);
Iinfra_KL_win_dist = mat2gray(Iinfra);
%% Undistortion the image
Iinfra_KL_win = kinect_undistort(Iinfra_KL_win_dist,kwin542_params,0);
Depth_KL_win_dist = double(Depth_KL_win);
Depth_KL_win = kinect_undistort(Depth_KL_win_dist,kwin542_params,0);
%% First chessboard detection
figure
imshow(Iinfra_KL_win);
hold on
[IR_KL_win_Points1,IR_KL_win_boardSize1] = detectCheckerboardPoints(Iinfra_KL_win);
plot(IR_KL_win_Points1(:,1), IR_KL_win_Points1(:,2), 'ro');
title('1');
%% Mask first chessboard
IR_KL_win_Points1 = round(IR_KL_win_Points1);
x1 = min(IR_KL_win_Points1(:,1));
y1 = min(IR_KL_win_Points1(:,2));
x2 = max(IR_KL_win_Points1(:,1));
y2 = max(IR_KL_win_Points1(:,2));
square_width = IR_KL_win_Points1(20,2) - IR_KL_win_Points1(16,2) + 1;
Iinfra2_KL_win  = Iinfra_KL_win;
Iinfra2_KL_win(y1-square_width:y2+square_width,x1-square_width:x2+square_width) = 0;
%% Second chessboard detection
figure
imshow(Iinfra2_KL_win);
hold on
[IR_KL_win_Points2,IR_KL_win_boardSize2] = detectCheckerboardPoints(Iinfra2_KL_win);
plot(IR_KL_win_Points2(:,1), IR_KL_win_Points2(:,2), 'ro');
title('2');
%% Mask second chessboard
IR_KL_win_Points2 = round(IR_KL_win_Points2);
x1 = min(IR_KL_win_Points2(:,1));
y1 = min(IR_KL_win_Points2(:,2));
x2 = max(IR_KL_win_Points2(:,1));
y2 = max(IR_KL_win_Points2(:,2));
square_width = IR_KL_win_Points2(20,2) - IR_KL_win_Points2(16,2) + 1;
Iinfra3_KL_win  = Iinfra2_KL_win;
Iinfra3_KL_win(y1-square_width:y2+square_width,x1-square_width:x2+square_width) = 0;
%% Third chessboard detection
figure
imshow(Iinfra3_KL_win);
hold on
[IR_KL_win_Points3,IR_KL_win_boardSize3] = detectCheckerboardPoints(Iinfra3_KL_win);
IR_KL_win_Points3 = round(IR_KL_win_Points3);
plot(IR_KL_win_Points3(:,1), IR_KL_win_Points3(:,2), 'ro');
title('3');
%% Whole points are here
IR_KL_win_Points = [IR_KL_win_Points1;IR_KL_win_Points2;IR_KL_win_Points3];
%% Point cloud generation
Depth_KL_win = double(Depth_KL_win)/1000;
IR_KL_win_Points = round(IR_KL_win_Points);
sizeDepth=size(Depth_KL_win);
xRow=1:sizeDepth(2);
yCol=1:sizeDepth(1);
X=repmat(xRow,sizeDepth(1),1);
Y=repmat(yCol',1,sizeDepth(2));
xBuff=( X - Px_kwin542 ).*( Depth_KL_win ./ Fx_kwin542);
yBuff=( Y - Py_kwin542 ).*( Depth_KL_win ./ Fy_kwin542);
RealW_KL_win_Points(length(IR_KL_win_Points),3)=0;
for i = 1:length(IR_KL_win_Points)
    RealW_KL_win_Points(i,1) = xBuff(IR_KL_win_Points(i,2),IR_KL_win_Points(i,1));
    RealW_KL_win_Points(i,2) = yBuff(IR_KL_win_Points(i,2),IR_KL_win_Points(i,1));
    RealW_KL_win_Points(i,3) = Depth_KL_win(IR_KL_win_Points(i,2),IR_KL_win_Points(i,1));
end
xBuf = reshape(xBuff,sizeDepth(1)*sizeDepth(2),1);
yBuf = reshape(yBuff,sizeDepth(1)*sizeDepth(2),1);
zBuf = reshape(Depth_KL_win,sizeDepth(1)*sizeDepth(2),1);
pcl_KL_win = [xBuf(:),yBuf(:),zBuf(:)];
%% read chessboards setup depth and infrared data of kwin sensor
I = imread([data_path 'setup_rgbd_data\kxbox_setup_rgbd\infraRed\infraRed00100.png']);
Depth_KR_xbox = imread([data_path 'setup_rgbd_data\kxbox_setup_rgbd\DEPTH\depth00100.png']);
%% Infrared image normalization
Id = double(I);
InfraredSourceValueMaximum = 65535;
InfraredSceneValueAverage = 0.02;
InfraredSceneStandardDeviations = 3.0;
Id = Id ./ InfraredSourceValueMaximum;
Id = Id ./ (InfraredSceneValueAverage * InfraredSceneStandardDeviations);
Id(Id > 1.0) = 1;
Id(Id < 0.01) = 0.01;
Id = Id .* 255;
Iinfra = uint16(Id);
Iinfra_KR_xbox_dist = mat2gray(Iinfra);
%% Undistortion the image
Iinfra_KR_xbox = kinect_undistort(Iinfra_KR_xbox_dist,kxbox_params,0);
Depth_KR_xbox_dist = double(Depth_KR_xbox);
Depth_KR_xbox = kinect_undistort(Depth_KR_xbox_dist,kxbox_params,0);
%% First chessboard detection
figure
imshow(Iinfra_KR_xbox);
hold on
[IR_KR_xbox_Points1,IR_KR_xbox_boardSize1] = detectCheckerboardPoints(Iinfra_KR_xbox);
IR_KR_xbox_Points1_x = IR_KR_xbox_Points1(:,1);
IR_KR_xbox_Points1_y = IR_KR_xbox_Points1(:,2);
IR_KR_xbox_Points1_x2 = reshape(IR_KR_xbox_Points1_x,IR_KR_xbox_boardSize1(1)-1,IR_KR_xbox_boardSize1(2)-1);
IR_KR_xbox_Points1_y2 = reshape(IR_KR_xbox_Points1_y,IR_KR_xbox_boardSize1(1)-1,IR_KR_xbox_boardSize1(2)-1);
IR_KR_xbox_Points1_x2 = flip(IR_KR_xbox_Points1_x2,1);
IR_KR_xbox_Points1_y2 = flip(IR_KR_xbox_Points1_y2,1);
IR_KR_xbox_Points1_x2 = IR_KR_xbox_Points1_x2(:);
IR_KR_xbox_Points1_y2 = IR_KR_xbox_Points1_y2(:);
IR_KR_xbox_Points1 = [IR_KR_xbox_Points1_x2 IR_KR_xbox_Points1_y2];
plot(IR_KR_xbox_Points1(:,1), IR_KR_xbox_Points1(:,2), 'ro');
%% Mask first chessboard
IR_KR_xbox_Points1 = round(IR_KR_xbox_Points1);
x1 = min(IR_KR_xbox_Points1(:,1));
y1 = min(IR_KR_xbox_Points1(:,2));
x2 = max(IR_KR_xbox_Points1(:,1));
y2 = max(IR_KR_xbox_Points1(:,2));
square_width = IR_KR_xbox_Points1(20,2) - IR_KR_xbox_Points1(16,2) + 1;
Iinfra2_KR_xbox  = Iinfra_KR_xbox;
Iinfra2_KR_xbox(y1-square_width:y2+square_width,x1-square_width:x2+square_width) = 0;
%% Second chessboard detection
figure
imshow(Iinfra2_KR_xbox);
hold on
[IR_KR_xbox_Points2,IR_KR_xbox_boardSize2] = detectCheckerboardPoints(Iinfra2_KR_xbox);
IR_KR_xbox_Points2_x = IR_KR_xbox_Points2(:,1);
IR_KR_xbox_Points2_y = IR_KR_xbox_Points2(:,2);
IR_KR_xbox_Points2_x2 = reshape(IR_KR_xbox_Points2_x,IR_KR_xbox_boardSize2(1)-1,IR_KR_xbox_boardSize2(2)-1);
IR_KR_xbox_Points2_y2 = reshape(IR_KR_xbox_Points2_y,IR_KR_xbox_boardSize2(1)-1,IR_KR_xbox_boardSize2(2)-1);
IR_KR_xbox_Points2_x2 = flip(IR_KR_xbox_Points2_x2,1);
IR_KR_xbox_Points2_y2 = flip(IR_KR_xbox_Points2_y2,1);
IR_KR_xbox_Points2_x2 = IR_KR_xbox_Points2_x2(:);
IR_KR_xbox_Points2_y2 = IR_KR_xbox_Points2_y2(:);
IR_KR_xbox_Points2 = [IR_KR_xbox_Points2_x2 IR_KR_xbox_Points2_y2];
plot(IR_KR_xbox_Points2(:,1), IR_KR_xbox_Points2(:,2), 'ro');
%% Mask second chessboard
IR_KR_xbox_Points2 = round(IR_KR_xbox_Points2);
x1 = min(IR_KR_xbox_Points2(:,1));
y1 = min(IR_KR_xbox_Points2(:,2));
x2 = max(IR_KR_xbox_Points2(:,1));
y2 = max(IR_KR_xbox_Points2(:,2));
square_width = IR_KR_xbox_Points2(20,2) - IR_KR_xbox_Points2(16,2) + 1;
Iinfra3_KR_xbox  = Iinfra2_KR_xbox;
Iinfra3_KR_xbox(y1-square_width:y2+square_width,x1-square_width:x2+square_width) = 0;
%% Third chessboard detection
figure
imshow(Iinfra3_KR_xbox);
hold on
[IR_KR_xbox_Points3,IR_KR_xbox_boardSize3] = detectCheckerboardPoints(Iinfra3_KR_xbox);
IR_KR_xbox_Points3_x = IR_KR_xbox_Points3(:,1);
IR_KR_xbox_Points3_y = IR_KR_xbox_Points3(:,2);
IR_KR_xbox_Points3_x2 = reshape(IR_KR_xbox_Points3_x,IR_KR_xbox_boardSize3(1)-1,IR_KR_xbox_boardSize3(2)-1);
IR_KR_xbox_Points3_y2 = reshape(IR_KR_xbox_Points3_y,IR_KR_xbox_boardSize3(1)-1,IR_KR_xbox_boardSize3(2)-1);
IR_KR_xbox_Points3_x2 = flip(IR_KR_xbox_Points3_x2,1);
IR_KR_xbox_Points3_y2 = flip(IR_KR_xbox_Points3_y2,1);
IR_KR_xbox_Points3_x2 = IR_KR_xbox_Points3_x2(:);
IR_KR_xbox_Points3_y2 = IR_KR_xbox_Points3_y2(:);
IR_KR_xbox_Points3 = [IR_KR_xbox_Points3_x2 IR_KR_xbox_Points3_y2];
plot(IR_KR_xbox_Points3(:,1), IR_KR_xbox_Points3(:,2), 'ro');
%% Whole points are here
%%%%% NOTE %%%%%%
%%% the chessboards might not be detected in the same order in two Kinects
%%% infrared images. Thus, you probably need to find the matched
%%% chessboards in Iinfra2_KL_win and Iinfra2_KR_xbox infrared images and 
%%% put the IR_KR_xbox_Points1, IR_KR_xbox_Points2 and IR_KR_xbox_Points3 
%%% in the correct order to make IR_KR_xbox_Points (line 204).
%%% To do this,  look at the first 3 figures of IR_KL_win detcted chessboards.
%%% Then look at the forth image and find the one between the first 3  
%%% figures. This figure title (which can be 1, 2 or 3) shows the first 
%%% point set component of IR_KR_xbox_Points. Do similarly for the other 
%%% two remaining ones. If the final point clouds are not logically 
%%% aligned, it means the order of the IR_KR_xbox_Points point sets is 
%%% not correct. 
IR_KR_xbox_Points = [IR_KR_xbox_Points1;IR_KR_xbox_Points3;IR_KR_xbox_Points2];
%% Point cloud generation
Depth_KR_xbox = double(Depth_KR_xbox)/1000;
IR_KR_xbox_Points = round(IR_KR_xbox_Points);
sizeDepth=size(Depth_KR_xbox);
xRow=1:sizeDepth(2);
yCol=1:sizeDepth(1);
X=repmat(xRow,sizeDepth(1),1);
Y=repmat(yCol',1,sizeDepth(2));
xBuff=( X - Px_kxbox ).*( Depth_KR_xbox ./ Fx_kxbox );
yBuff=( Y - Py_kxbox ).*( Depth_KR_xbox ./ Fy_kxbox );
RealW_KR_xbox_Points(length(IR_KR_xbox_Points),3)=0;
for i = 1:length(IR_KR_xbox_Points)
    RealW_KR_xbox_Points(i,1) = xBuff(IR_KR_xbox_Points(i,2),IR_KR_xbox_Points(i,1));
    RealW_KR_xbox_Points(i,2) = yBuff(IR_KR_xbox_Points(i,2),IR_KR_xbox_Points(i,1));
    RealW_KR_xbox_Points(i,3) = Depth_KR_xbox(IR_KR_xbox_Points(i,2),IR_KR_xbox_Points(i,1));
end
xBuf = reshape(xBuff,sizeDepth(1)*sizeDepth(2),1);
yBuf = reshape(yBuff,sizeDepth(1)*sizeDepth(2),1);
zBuf = reshape(Depth_KR_xbox,sizeDepth(1)*sizeDepth(2),1);
pcl_KR_xbox = [xBuf(:),yBuf(:),zBuf(:)];
%% Align Point Clouds with Besl method
[ret_R, ret_t] = BeslTransform(RealW_KL_win_Points, RealW_KR_xbox_Points);
A2 = (ret_R*RealW_KL_win_Points') + repmat(ret_t, 1, length(RealW_KL_win_Points));
RealW_KL_win_Points2 = A2';
error = RealW_KL_win_Points2 - RealW_KR_xbox_Points;
error = error .* error;
error = sum(error(:));
rmse = sqrt(error/length(RealW_KL_win_Points))
pcl_KL_win_Btransformed = (ret_R*pcl_KL_win') + repmat(ret_t, 1, length(pcl_KL_win));
pcl_KL_win_Btransformed2 = pcl_KL_win_Btransformed';
figure;pcshowpair(pointCloud(pcl_KL_win_Btransformed2),pointCloud(pcl_KR_xbox));
%%% Note that the final aligned point clouds are noisy because the depth
%%% images have been undistorted. It is not important as here the aim is
%%% only computing R and T and use them in reconstruction.
save([data_path 'R_transform.mat'],'ret_R');
save([data_path 'T_transform.mat'],'ret_t');
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
