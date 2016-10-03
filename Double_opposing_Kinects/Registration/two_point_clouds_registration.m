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
clear all
close all
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
%% load rotation and transformation matrices created by running compute_R_T.m source code
load([data_path 'R_transform.mat']);
load([data_path 'T_transform.mat']);
%% define two point clouds dedicated rgbd data
kinect_win_path_folder = [data_path 'reconstruction_rgbd_data\kwin_rgbd_data\2016-04-13-11_00-08\'];
kinect_xbox_path_folder = [data_path 'reconstruction_rgbd_data\kxbox_rgbd_data\2016-04-13-11_00-08\'];
%% start frame adjustment
depth_start_frame = 390;
%% read depth meta data files
win_depth_fileID = fopen([kinect_win_path_folder 'depthMeta.txt']);
win_depth_meta = textscan(win_depth_fileID, '%u32, %d, %u64, %f');
win_depth_mts = win_depth_meta{1,1};
win_depth_frames = win_depth_meta{1,2};
win_depth_kts = win_depth_meta{1,3};
win_depth_tbbts = win_depth_meta{1,4};
xbox_depth_fileID = fopen([kinect_xbox_path_folder 'depthMeta.txt']);
xbox_depth_meta = textscan(xbox_depth_fileID, '%u32, %d, %u64, %f');
xbox_depth_mts = xbox_depth_meta{1,1};
xbox_depth_frames = xbox_depth_meta{1,2};
xbox_depth_kts = xbox_depth_meta{1,3};
xbox_depth_tbbts = xbox_depth_meta{1,4};
%% read rgb meta data files
win_rgb_fileID = fopen([kinect_win_path_folder 'rgbMeta.txt']);
win_rgb_meta = textscan(win_rgb_fileID, '%u32, %d, %u64, %f');
win_rgb_mts = win_rgb_meta{1,1};
win_rgb_frames = win_rgb_meta{1,2};
win_rgb_kts = win_rgb_meta{1,3};
win_rgb_tbbts = win_rgb_meta{1,4};
xbox_rgb_fileID = fopen([kinect_xbox_path_folder 'rgbMeta.txt']);
xbox_rgb_meta = textscan(xbox_rgb_fileID, '%u32, %d, %u64, %f');
xbox_rgb_mts = xbox_rgb_meta{1,1};
xbox_rgb_frames = xbox_rgb_meta{1,2};
xbox_rgb_kts = xbox_rgb_meta{1,3};
xbox_rgb_tbbts = xbox_rgb_meta{1,4};
%% find nspire frame corresponding timestamps
win_nspire_depth_mts = win_depth_mts(depth_start_frame+1);
win_nspire_depth_kts = win_depth_kts(depth_start_frame+1);
win_nspire_depth_tbbts = win_depth_tbbts(depth_start_frame+1);
win_nspire_depth_frame = win_depth_frames(depth_start_frame+1);
min_find_tmp = abs(int32(xbox_depth_mts) - int32(win_nspire_depth_mts));
[v,iv] = min(min_find_tmp);
xbox_nspire_depth_crs_mts = xbox_depth_mts(iv);
xbox_nspire_depth_crs_kts = xbox_depth_kts(iv);
xbox_nspire_depth_crs_tbbts = xbox_depth_tbbts(iv);
xbox_nspire_depth_crs_frame = xbox_depth_frames(iv);
win_depth_counter = win_nspire_depth_frame + 1;
xbox_depth_counter = xbox_nspire_depth_crs_frame + 1;
%% list of depth images
win_depth_dir = dir(fullfile(kinect_win_path_folder,'DEPTH\*.png'));
xbox_depth_dir = dir(fullfile(kinect_xbox_path_folder,'DEPTH\*.png'));
win_rgb_dir = dir(fullfile(kinect_win_path_folder,'RGB\*.jpg'));
xbox_rgb_dir = dir(fullfile(kinect_xbox_path_folder,'RGB\*.jpg'));
%% An example of registered point cloud visualisation
merged_pc = figure(1);
%% geting RGB and depth frames
while (win_depth_counter < length(win_depth_dir) && xbox_depth_counter < length(xbox_depth_dir))
% while (win_depth_counter < 430 && xbox_depth_counter < 430)
    %% find corresponding RGB frames
    min_find_rgb_tmp = abs(int64(win_rgb_kts) - int64(win_depth_kts(win_depth_counter)));
    [v_rgb,iv_rgb] = min(min_find_rgb_tmp);
    win_curr_rgb_mts = win_rgb_mts(iv_rgb);
    win_curr_rgb_kts = win_rgb_kts(iv_rgb);
    win_curr_rgb_tbbts = win_rgb_tbbts(iv_rgb);
    win_curr_rgb_frame = win_rgb_frames(iv_rgb);
    min_find_xrgb_tmp = abs(int64(xbox_rgb_kts) - int64(xbox_depth_kts(xbox_depth_counter)));
    [v_xrgb,iv_xrgb] = min(min_find_xrgb_tmp);
    xbox_curr_rgb_mts = xbox_rgb_mts(iv_xrgb);
    xbox_curr_rgb_kts = xbox_rgb_kts(iv_xrgb);
    xbox_curr_rgb_tbbts = xbox_rgb_tbbts(iv_xrgb);
    xbox_curr_rgb_frame = xbox_rgb_frames(iv_xrgb);
    %% get rgb file names
    win_depth_filename = win_depth_dir(win_depth_counter).name;
    xbox_depth_filename = xbox_depth_dir(xbox_depth_counter).name;
    win_rgb_filename = win_rgb_dir(win_curr_rgb_frame+1).name;
    xbox_rgb_filename = xbox_rgb_dir(xbox_curr_rgb_frame+1).name;
    %% load kwin depth and rgb images and generate point clouds
    win_depth_I = imread([kinect_win_path_folder 'DEPTH\' win_depth_filename]);
    win_RGB_I = imread([kinect_win_path_folder 'RGB\' win_rgb_filename]);
    [undist_win_depth,aligned_win_rgb]=depth2rgb(win_depth_I,win_RGB_I,kwin_serial,1,data_path);
    win_depth_I = double(win_depth_I)/1000;
    sizeDepth=size(win_depth_I);
    xRow=1:sizeDepth(2);
    yCol=1:sizeDepth(1);
    X=repmat(xRow,sizeDepth(1),1);
    Y=repmat(yCol',1,sizeDepth(2));
    xBuff=( X - Px_kwin542 ).*( win_depth_I ./ Fx_kwin542);
    yBuff=( Y - Py_kwin542 ).*( win_depth_I ./ Fy_kwin542);   
    xBuf = reshape(xBuff,sizeDepth(1)*sizeDepth(2),1);
    yBuf = reshape(yBuff,sizeDepth(1)*sizeDepth(2),1);
    zBuf = reshape(win_depth_I,sizeDepth(1)*sizeDepth(2),1);
    win_RGB_Buf = reshape(aligned_win_rgb,sizeDepth(1)*sizeDepth(2),3);
    pcl_win = [xBuf,yBuf,zBuf];    
    %% load kxbox depth and rgb images and generate point clouds
    xbox_depth_I = imread([kinect_xbox_path_folder 'DEPTH\' xbox_depth_filename]);
    xbox_RGB_I = imread([kinect_xbox_path_folder 'RGB\' xbox_rgb_filename]);
    [undist_xbox_depth,aligned_xbox_rgb]=depth2rgb(xbox_depth_I,xbox_RGB_I,kxbox_serial,1,data_path);
    xbox_depth_I = double(xbox_depth_I)/1000;
    sizeDepth=size(xbox_depth_I);
    xRow=1:sizeDepth(2);
    yCol=1:sizeDepth(1);
    X=repmat(xRow,sizeDepth(1),1);
    Y=repmat(yCol',1,sizeDepth(2));
    xBuff=( X - Px_kxbox ).*( xbox_depth_I ./ Fx_kxbox);
    yBuff=( Y - Py_kxbox ).*( xbox_depth_I ./ Fy_kxbox);   
    xBuf = reshape(xBuff,sizeDepth(1)*sizeDepth(2),1);
    yBuf = reshape(yBuff,sizeDepth(1)*sizeDepth(2),1);
    zBuf = reshape(xbox_depth_I,sizeDepth(1)*sizeDepth(2),1);
    xbox_RGB_Buf = reshape(aligned_xbox_rgb,sizeDepth(1)*sizeDepth(2),3);
    pcl_xbox = [xBuf,yBuf,zBuf];
    RGB_pcl_xbox = pointCloud(pcl_xbox,'Color',xbox_RGB_Buf);
    %% transform pcl_win point cloud and merge with pcl_xbox    
    pcl_win_Btransformed = (ret_R*pcl_win') + repmat(ret_t, 1, length(pcl_win));
    pcl_win_Btransformed2 = pcl_win_Btransformed';
    RGB_pcl_win_Btransformed2 = pointCloud(pcl_win_Btransformed2,'Color',win_RGB_Buf);
    RGB_merged_pc = pcmerge(RGB_pcl_win_Btransformed2,RGB_pcl_xbox,0.0015);       
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%% RGB_merged_pc is the merged final point cloud which can be used %%%
    %%% It can be written to separate ply files or can be used in video for
    %%% demonstration.
    pcshow(RGB_merged_pc);
    zlim([-4.92192412518962 7.951]);
    xlim([-5.386340138122128 5.322178305859697]);
    ylim([-3.9473279890351103 4.743820237750637]);
    %%%%%%%%%%%%%%%%
    camva('manual');
    camva(10.813145071246478);
    %%%%%%%%%%%%%%%%
    camtarget('manual');
    camtarget([-0.02134105420223163,-0.6831214972736571,1.485860916327762]);
    %%%%%%%%%%%%%%%%
    camup('manual');
    camup([0.6252886948887708,-0.7719887109610861,0.11422555840501723]);
    %%%%%%%%%%%%%%%%
    campos('manual');
    campos([-21.169139587387008,-18.290929617636657,-1.7494023142801323]);
    %%%%%%%%%%%%%%%
    set(gca,'xtick',[],'ytick',[],'ztick',[]);
    grid off;
    box off;
    drawnow;
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%    
    win_depth_counter = win_depth_counter + 1;
    xbox_depth_counter = xbox_depth_counter + 1;
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