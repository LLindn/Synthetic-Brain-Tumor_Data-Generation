//----------------------------------------------------------------------------------
//! The ML module class GenerateTumor.
/*!
// \file   
// \author  LL
//
// 
*/
//----------------------------------------------------------------------------------

#include "mlGenerateTumor.h"
#include <random>

ML_START_NAMESPACE

//! Implements code for the runtime type system of the ML
ML_MODULE_CLASS_SOURCE(GenerateTumor, Module);

//----------------------------------------------------------------------------------

GenerateTumor::GenerateTumor() : Module(1, 0)
{
	FieldContainer *fields = getFieldContainer();

	_generateTumor = addNotify("GenerateTumor");

	handleNotificationOff();

	_separatorPolyhedron = new SoSeparator();

	(_outSoPolyhedron = fields->addSoNode("outputPolyhedron"))->setSoNodeValue(_separatorPolyhedron);


	_vPropPolyhedron = new SoVertexProperty();

	if (_vPropPolyhedron)
	{
		_separatorPolyhedron->addChild(_vPropPolyhedron);
	}


	_faceSetPolyhedron = new SoIndexedFaceSet();

	if (_faceSetPolyhedron)
	{
		_separatorPolyhedron->addChild(_faceSetPolyhedron);
		_faceSetPolyhedron->vertexProperty = _vPropPolyhedron;
		_faceSetPolyhedron->coordIndex.setValues(0, 0, 0);
	}


	// Reactivate calls of handleNotification on field changes.
	handleNotificationOn();


	// Activate inplace data buffers for output outputIndex and input inputIndex.
	// setOutputImageInplace(outputIndex, inputIndex);

	// Activate page data bypass from input inputIndex to output outputIndex.
	// Note that the module must still be able to calculate the output image.
	// setBypass(outputIndex, inputIndex);

	// Declare that this module supports all voxel types by default, the real supported
	// subset will be enforced by SyntheticTumorsOutputImageHandler::verifyProperties()
	setVoxelDataTypeSupport(ALL_REGISTERED_TYPES);

	_vVolumeGV = 0;
}

//----------------------------------------------------------------------------------

void GenerateTumor::handleNotification(Field* field)
{
	// Handle changes of module parameters and input image fields here.
	bool touchOutputs = false;
	if (isInputImageField(field))
	{
		touchOutputs = true;
	}


	if (field == _generateTumor)
	{

		if (_vVolumeGV == 0)
		{
			std::cout << "_vVolumeGV == 0" << std::endl;
			return;
		}

		ml::Vector extentGV = getInputImage(0)->getImageExtent();
		//_vVolumeGV,
		int tmpX = 0;
		int tmpY = 0;
		int tmpZ = 0;

		int tmpGV = 0;
		if (tmpX >= 0 && tmpX < ((extentGV.x) - 1))
		{
			if (tmpY >= 0 && tmpY < ((extentGV.y) - 1))
			{
				if (tmpZ >= 0 && tmpZ < ((extentGV.z) - 1))
				{
					ml::Vector cursorPos;
					cursorPos.set(tmpX, tmpY, tmpZ, 0, 0, 0);
					_vVolumeGV->setCursorPos(cursorPos);
				}
			}
		}

		getInField(0)->touch();

		CtPolyhedron _poly(4, 5, 0);

		// Reset the vertex property settings.
		_vPropPolyhedron->vertex.deleteValues(0);
		_vPropPolyhedron->orderedRGBA.deleteValues(0);
		_vPropPolyhedron->materialBinding.setValue(SoVertexProperty::OVERALL);

		// Reset the vertex property settings.
		_faceSetPolyhedron->coordIndex.deleteValues(0);

		//(initial polyhedra)
		std::vector<float> pointCoords = _poly.getVecPointCoords();
		std::vector<int> facePoints = _poly.getVecFacePoints();
		std::vector<uint32_t> rgbas = _poly.getVecRgbas();


		_vPropPolyhedron->enableNotify(false);

		_vPropPolyhedron->vertex.setValues(0, pointCoords.size() / 3, (const float(*)[3])&(pointCoords[0]));
		_vPropPolyhedron->orderedRGBA.setValues(0, rgbas.size(), &(rgbas[0]));
		_vPropPolyhedron->materialBinding.setValue(SoVertexProperty::PER_VERTEX_INDEXED);

		_faceSetPolyhedron->coordIndex.setValues(0, facePoints.size(), (const int *)&(facePoints[0]));

		_vPropPolyhedron->enableNotify(true);

		uint32_t uColor = SbColor(1.f, 0.f, 0.f).getPackedValue();

		_outSoPolyhedron->touch();
		touchOutputs = true;

	}


	if (field == getInField(0))
	{
		const PagedImg* inImg = 0;
		inImg = getUpdatedInImg(0);

		if (inImg == 0)
		{
			std::cout << "No Input Image" << std::endl;
			return;
		}

		if (_vVolumeGV != 0)
			delete _vVolumeGV;

		// set TVirtualVolume
		_vVolumeGV = new TVirtualVolume<MLint16>(this, 0, MLint16Type);


	} 

	if (field == getInField(1))
	{
		std::cout << "getInField(1): start " << std::endl;
	}

	if (isInputImageField(field))
	{
		touchOutputs = true;
	}

	if (touchOutputs)
	{
		// Touch all output image fields to notify connected modules.
		touchOutputImageFields();
	}
}

//----------------------------------------------------------------------------------

void GenerateTumor::activateAttachments()
{
  // Update members to new field state here.
  // Call super class functionality to enable notification handling again.
  Module::activateAttachments();
}

//----------------------------------------------------------------------------------

Module::INPUT_HANDLE GenerateTumor::handleInput(int /*inputIndex*/, INPUT_STATE /*state*/) const
{
	return Module::ALLOW_INVALID_INPUT;
}

//----------------------------------------------------------------------------------

void GenerateTumor::calculateOutputImageProperties(int /*outputIndex*/, PagedImage* outputImage)
{
  // Change properties of output image outputImage here whose
  // defaults are inherited from the input image 0 (if there is one).

  // Set output image to a fixed type.
  //outputImage->setDataType(MLdoubleType);

  // Specify input sub-image data types (otherwise the above output data type is used for all input sub-images).
  //outputImage->setInputSubImageDataType(0, getInputImage(0)->getDataType());
  //outputImage->setInputSubImageDataType(1, getInputImage(1)->getDataType());
}

//----------------------------------------------------------------------------------

SubImageBox GenerateTumor::calculateInputSubImageBox(int inputIndex, const SubImageBox& outputSubImageBox, int outputIndex)
{
  // Return region of input image inputIndex needed to compute region
  // outSubImgBox of output image outputIndex.
  return outputSubImageBox;
}


//----------------------------------------------------------------------------------

ML_CALCULATEOUTPUTSUBIMAGE_NUM_INPUTS_2_SCALAR_TYPES_CPP(GenerateTumor);

template <typename T>
void GenerateTumor::calculateOutputSubImage(TSubImage<T>* outputSubImage, int outputIndex
                                     , TSubImage<T>* inputSubImage0
                                     , TSubImage<T>* inputSubImage1
                                     )
{
  // Compute sub-image of output image outputIndex from input sub-images.

  // Clamp box of output image against image extent to avoid that unused areas are processed.
  const SubImageBox validOutBox = outputSubImage->getValidRegion();

  // Process all voxels of the valid region of the output page.
  ImageVector p;
  for (p.u=validOutBox.v1.u;  p.u<=validOutBox.v2.u;  ++p.u) {
    for (p.t=validOutBox.v1.t;  p.t<=validOutBox.v2.t;  ++p.t) {
      for (p.c=validOutBox.v1.c;  p.c<=validOutBox.v2.c;  ++p.c) {
        for (p.z=validOutBox.v1.z;  p.z<=validOutBox.v2.z;  ++p.z) {
          for (p.y=validOutBox.v1.y;  p.y<=validOutBox.v2.y;  ++p.y) {

            p.x = validOutBox.v1.x;
            // Get pointers to row starts of input and output sub-images.
            const T* inVoxel0 = inputSubImage0->getImagePointer(p);

            T*  outVoxel = outputSubImage->getImagePointer(p);

            const MLint rowEnd   = validOutBox.v2.x;

            // Process all row voxels.
            for (; p.x <= rowEnd;  ++p.x, ++outVoxel, ++inVoxel0)
            {
              *outVoxel = *inVoxel0;
            }
          }
        }
      }
    }
  }
}

ML_END_NAMESPACE