clc; clear all; close all;

tbl0 = readtable('DataAcquisitionModule.csv');
tbl1 = readtable('Orientation1.csv');
tbl2 = readtable('Orientation2.csv');
tbl3 = readtable('Orientation3.csv');

t_cutoff = 15e3;
[~, i_cutoff_0] = min(abs(tbl0.Var1-t_cutoff));
[~, i_cutoff_1] = min(abs(tbl1.Var1-t_cutoff));
[~, i_cutoff_2] = min(abs(tbl2.Var1-t_cutoff));
[~, i_cutoff_3] = min(abs(tbl3.Var1-t_cutoff));

tbl0 = tbl0(1:i_cutoff_0,:);
tbl1 = tbl1(1:i_cutoff_1,:);
tbl2 = tbl2(1:i_cutoff_2,:);
tbl3 = tbl3(1:i_cutoff_3,:);

max_loc0 = islocalmax(tbl0.Var2);
max_loc1 = islocalmax(tbl1.Var2);
max_loc2 = islocalmax(tbl2.Var2);
max_loc3 = islocalmax(tbl3.Var2);

T_0 = mean(diff(tbl0.Var1(max_loc0)));
T_1 = mean(diff(tbl1.Var1(max_loc1)));
T_2 = mean(diff(tbl2.Var1(max_loc2)));
T_3 = mean(diff(tbl3.Var1(max_loc3)));

figure;
plot(1e-3 * tbl0.Var1, tbl0.Var2)
hold on;
plot(1e-3 * tbl0.Var1(max_loc0), tbl0.Var2(max_loc0),'r*')
xlabel('Time [s]')
ylabel('Roll [deg]')
title('Data Acquisition Module')

figure;
plot(1e-3 * tbl1.Var1, tbl1.Var2)
hold on;
plot(1e-3 * tbl1.Var1(max_loc1), tbl1.Var2(max_loc1),'r*')
xlabel('Time [s]')
ylabel('Roll [deg]')
title('Orientation 1: I_x')

figure;
plot(1e-3 * tbl2.Var1, tbl2.Var2)
hold on;
plot(1e-3 * tbl2.Var1(max_loc2), tbl2.Var2(max_loc2),'r*')
xlabel('Time [s]')
ylabel('Roll [deg]')
title('Orientation 2: I_z')

figure;
plot(1e-3 * tbl3.Var1, tbl3.Var2)
hold on;
plot(1e-3 * tbl3.Var1(max_loc3), tbl3.Var2(max_loc3),'r*')
xlabel('Time [s]')
ylabel('Roll [deg]')
title('Orientation 3: I_y')

R = 8.25e-2;
L = 31e-1;
g = 9.8;
M_FS = 129e-3;
M_DAM = 68e-3;

I_DAM = R^2 * g * T_0 / (4*pi^2*L) * M_DAM

I_FS_x = R^2 * g * T_1 / (4*pi^2*L) * (M_FS + M_DAM) - I_DAM
I_FS_z = R^2 * g * T_2 / (4*pi^2*L) * (M_FS + M_DAM) - I_DAM
I_FS_y = R^2 * g * T_3 / (4*pi^2*L) * (M_FS + M_DAM) - I_DAM

