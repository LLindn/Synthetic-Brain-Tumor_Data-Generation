# Synthetic GBM Data Generation in MeVisLab

MeVisLab network for the semi-automatic generation of synthetic MRI data of glioblastomas (GBMs) and automatic creation of the corresponding ground truth.

* Enhancing tumor margin and necrotic core of a glioblastoma are simulated 
* Binary ground truth segmentation (of the enhancing tumor together with the necrotic core) is automatically generated
* Additionally a simplified tumor mass effect can be simulated


## Requirements

To use the network, you need:

1. [MeVisLab](https://www.mevislab.de/download/) 3.0.1 
2. A valid [MeVisLab](https://www.mevislab.de/download/) license


## Setup

1. Clone the repository: ```git clone https://github.com/LLindn/Synthetic-Brain-Tumor_Data-Generation.git```
2. Open MeVisLab
3. Navigate to **Edit -> Preferences...** and select the section _Packages_. Click on _"Add Existing User Packages"_
to include the folder ```General``` located in ```Custom_Package```.


## Getting Started

Open the file ```ArtificialTumor.mlab``` (located in the MeVisLab_Network folder), which contains the MeVisLab network for synthetic data generation.

### Data generation steps:

1. Load 3D MRI data (nrrd or nifti format) of a healthy subject by using the _LoadBrainMRI_ module
2. Double click on the _SetSeedPoint_ module (if not already open). Select a seed point (by simply clicking on the MR image) at the desired tumor position.
3. Optional step to simulate a simplified tumor mass effect: Double click on the _SetSeedPointDeform_ Module (if not already open). Select a seed point (by simply clicking on the MR image) at the desired center of brain tissue deformation.
4. Double click on the _GenerateTumor_ module (if not already open) and subsequently click on "GenerateTumor" to generate a synthetic tumor structure. 
5. Click on the "refresh" symbol of the _CreateFinalData_ module (or double click on the module and then select "Update") to create the final synthetic MR image. This may take a few seconds.
You can examine the resulting MR image by double clicking on the _ViewFinalImage_ module. If you are not happy with the shape of the tumor you can create a new one by again using the _GenerateTumor_ module.
If you want to change the position of the tumor you can select a new seed point using the _SetSeedPoint_ module.
6. The MR image can be saved in single 2D slices (tiff or png format) by using the _SaveSlices_ module. Select a desired path and name for the synthetic MRI data and the corresponding ground truth segmentation. If you want to save the 3D volume, replace the _SaveSlices_ module with the standard MeVisLab _itkImageFileWriter_ module.


### Optional steps:

To change the intensity and size of the synthetic tumor, some manual modifications can optionally be performed after step 5.

These manual modifications are carried out in the internal network of the _ProcessTumor_ module. To open the internal network, 
right click on the _ProcessTumor_ module and select "Show Internal Network".

* **Change Tumor Intensity:** You can manually adapt the intensity of the synthetic tumor by changing the value of the _AdjustTumorIntensity_ module.
* **Change tumor size:** You can manually change the size of the tumor by by changing the value of the _SoScale_ module.


## License

This project is licensed under the MIT License - see the [LICENSE](https://github.com/LLindn/Synthetic-Brain-Tumor_Data-Generation/blob/master/LICENSE) file for details.
.

## Reference

If you use the provided code/network, please cite the following paper:

L. Lindner et al. _TuMore: Generation of Synthetic Brain Tumor MRI Data for Deep Learning Based Segmentation Approaches._ SPIE Medical Imaging, 2018.

