openExample("sm/RunFKOnHumanoidRobotArmExample");
mdl = "ImportedURDF";
load_system(mdl);
fk = simscape.multibody.KinematicsSolver(mdl);