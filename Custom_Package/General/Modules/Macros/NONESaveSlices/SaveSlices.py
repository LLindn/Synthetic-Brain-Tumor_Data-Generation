# ----------------------------------------------------------------------------

# 
#  \file    SaveSlices.py
#  \author  LL
#
#  

# ----------------------------------------------------------------------------

from mevis import *
import os
import math


def export_function():
  path_patient = ctx.field("file_path_patient").value
  path_mask = ctx.field("file_path_mask").value
  filename_patient = ctx.field("filename_patient").value
  filename_mask = ctx.field("filename_mask").value

  check_input_image, check_paths, check_slice_numb = check_input(path_patient, path_mask)

  # check if the paths exist and if the input parameters are okay
  if check_input_image == False:
    print("No image and mask inputs")
  elif check_paths == False:
    print("Invalid path")
  elif check_slice_numb == False:
    print("Invalid slice numbers")
  else:
    set_datatype()

    # export original slices
    save_slices_patient(path_patient, filename_patient)
    save_slices_mask(path_mask, filename_mask)
    print("Images exported")


# -----------------------------------------------------------------------------------------
# set data format
def set_datatype():
  ctx.field("SavePatient.format").value = ctx.field("data_type").value
  ctx.field("SaveMask.format").value = ctx.field("data_type").value


# -----------------------------------------------------------------------------------------
# Check Input
def check_input(path_patient, path_mask):
  check_input_image = True
  check_paths = True
  check_slice_numb = True

  if ctx.field("InfoPatient.sizeZ").value == 0 and \
          ctx.field("InfoMask.sizeZ").value != 0:
    print("No image input")

  if ctx.field("InfoMask.sizeZ").value == 0 and \
          ctx.field("InfoPatient.sizeZ").value != 0:
    print("No mask input")

  if ctx.field("InfoPatient.sizeZ").value == 0 and \
          ctx.field("InfoMask.sizeZ").value == 0:
    check_input_image = False

  if os.path.exists(path_patient) == False and os.path.isdir(path_patient) == False or \
              os.path.exists(path_mask) == False and os.path.isdir(path_mask) == False:
    check_paths = False

  if ctx.field("InfoPatient.sizeZ").value != 0:
    if ctx.field("first_slice").value > ctx.field("last_slice").value or \
            ctx.field("first_slice").value < 0 or ctx.field("last_slice").value < 0 or \
            ctx.field("first_slice").value >= ctx.field("InfoPatient.sizeZ").value or \
            ctx.field("last_slice").value >= ctx.field("InfoPatient.sizeZ").value:
      check_slice_numb = False

  if ctx.field("InfoPatient.sizeZ").value == 0 and \
          ctx.field("InfoMask.sizeZ").value != 0:
    if ctx.field("first_slice").value > ctx.field("last_slice").value or \
            ctx.field("first_slice").value < 0 or ctx.field("last_slice").value < 0 or \
            ctx.field("first_slice").value >= ctx.field("InfoMask.sizeZ").value or \
            ctx.field("last_slice").value >= ctx.field("InfoMask.sizeZ").value:
      check_slice_numb = False


  return check_input_image, check_paths, check_slice_numb



  # -----------------------------------------------------------------------------------------


# saves slices of the patient
def save_slices_patient(new_path, new_filename):
  progress_part = 0
  progress_counter = 0
  progress_finished = 1
  bool_every_slice = ctx.field("every_slice").value

  # parameters for saving all slices
  if bool_every_slice == True:
    number_slices = ctx.field("InfoPatient.sizeZ").value
    stop_slice = number_slices
    start_slice = 0

  # parameters for saving some slices
  else:
    start_slice = ctx.field("first_slice").value
    stop_slice = ctx.field("last_slice").value + 1  # +1 for correct loop
    number_slices = stop_slice - start_slice

  # loop for saving each slice
  for counter_slices in range(start_slice, stop_slice, 1):


    ctx.field("SavePatient.filename").value = os.path.join(new_path, new_filename + \
                                   "_Slice" + str(counter_slices))
    ctx.field("SubImagePatient.z").value = counter_slices
    ctx.field("SavePatient.startTaskSynchronous").touch()
    progress_counter += 1
    progress_part = float(progress_counter) / float(number_slices)
    ctx.field("export_progress").value = progress_part * 0.5

  ctx.field("export_progress").value = progress_finished * 0.5


# -----------------------------------------------------------------------------------------
# saves slices of the mask
def save_slices_mask(new_path, new_filename):
  progress_part = 0
  progress_counter = 0
  progress_finished = 1
  bool_every_slice = ctx.field("every_slice").value

  # parameters for saving all slices
  if bool_every_slice == True:
    number_slices = ctx.field("InfoMask.sizeZ").value
    stop_slice = number_slices
    start_slice = 0

  # parameters for saving some slices
  else:
    start_slice = ctx.field("first_slice").value
    stop_slice = ctx.field("last_slice").value + 1  # +1 for correct loop
    number_slices = stop_slice - start_slice

  # loop for saving each slice
  for counter_slices in range(start_slice, stop_slice, 1):

    ctx.field("SaveMask.filename").value = os.path.join(new_path, new_filename + \
                                "_Slice" + str(counter_slices))
    ctx.field("SubImageMask.z").value = counter_slices
    ctx.field("SaveMask.startTaskSynchronous").touch()
    progress_counter += 1
    progress_part = (float(progress_counter) / float(number_slices)) + 0.5
    ctx.field("export_progress").value = progress_part

  ctx.field("export_progress").value = progress_finished


# -----------------------------------------------------------------------------------------



