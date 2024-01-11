function SimPhiRL = getSimPhiRL(ThetaBeta)
tb = reshape(ThetaBeta, [2,1]);
PhiRL = [1 1; -1 1]* tb - [1; -1]*deg2rad(17);
SimPhiRL = [deg2rad(90-17) - PhiRL(1), deg2rad(90+17) - PhiRL(2)];
end
