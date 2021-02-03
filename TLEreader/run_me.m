clc; clear all; close all;

file_in = "TLE.txt";
fID = fopen(file_in,'r');
data = textscan(fID,'%s','Delimiter','\n');
data_arr = ["Satellite TLE"; data{1,1}{1}; data{1,1}{2}];
fclose(fID);

ke = TLE2KE(data_arr)
eci = KE2ECI(ke)

file_out = "KERV.txt";
fID = fopen(file_out,'w');
fprintf(fID,'Keplerian Elements\n');
fprintf(fID,'%.6f\n',ke);
fprintf(fID,'\nECI Position and Velocity\n');
fprintf(fID,'%.2f\n',eci);
fclose(fID);
