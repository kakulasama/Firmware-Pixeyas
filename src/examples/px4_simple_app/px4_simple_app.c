/****************************************************************************
 *
 *   Copyright (c) 2012-2016 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file px4_simple_app.c
 * Minimal application example for PX4 autopilot
 *
 * @author Example User <mail@example.com>
 */

#include <px4_config.h>
#include <px4_tasks.h>
#include <px4_posix.h>
#include <unistd.h>
#include <stdio.h>
#include <poll.h>
#include <string.h>
//#include <drivers/drv_hrt.h>

#include <uORB/uORB.h>
#include <uORB/topics/sensor_combined.h>
#include <uORB/topics/vehicle_attitude.h>
#include <uORB/topics/sonar_distance.h>
#include <uORB/topics/manual_control_setpoint.h>
#include <uORB/topics/distance_sensor.h>
#include <uORB/topics/ekf_localization.h>
#include <uORB/topics/manual_control_setpoint.h>
//#include <uORB/topics/alt_ctrl.h>

//__EXPORT int px4_simple_app_main(int argc, char *argv[]);
int px4_simple_app_main(int argc, char *argv[]);


int px4_simple_app_main(int argc, char *argv[]) {
//	PX4_INFO("Hello Sky!");
	/* advertise attitude topic */
	//struct vehicle_attitude_s att;
	//memset(&att, 0, sizeof(att));
	//orb_advert_t att_pub = orb_advertise(ORB_ID(vehicle_attitude), &att);
	//int sensor_sub_fd = orb_subscribe(ORB_ID(sonar_distance));
	//int mb12xx_sub_fd = orb_subscribe(ORB_ID(distance_sensor));
//	int mb12xx_sub_fd0 = orb_subscribe_multi(ORB_ID(distance_sensor), 0);
//	int mb12xx_sub_fd0 = orb_subscribe_multi(ORB_ID(distance_sensor), 0);
	//int mb12xx_sub_fd1 = orb_subscribe_multi(ORB_ID(distance_sensor), 1);
	int manual_sub=orb_subscribe(ORB_ID(manual_control_setpoint));
	//int sensor_sub_fd = orb_subscribe(ORB_ID(ekf_localization));
	//int sensor_distance_fd = orb_subscribe(ORB_ID(distance_sensor));

	//orb_set_interval(sensor_sub_fd, 50);	// limit the update rate to 5 Hz
//	orb_set_interval(sensor_sub_fd, 200);	// limit the update rate to 5 Hz
	//orb_set_interval(mb12xx_sub_fd1, 10);	// limit the update rate to 5 Hz

	//struct sonar_distance_s sonar;
	//memset(&sonar, 0, sizeof(sonar));

//	struct distance_sensor_s mb12xx_data0;
//	memset(&mb12xx_data0, 0, sizeof(mb12xx_data0));
	struct manual_control_setpoint_s manual;
	memset(&manual, 0, sizeof(manual));
//	struct ekf_localization_s mav_position;
//	memset(&mav_position, 0, sizeof(mav_position));

//	struct distance_sensor_s d_s;
//	memset(&d_s, 0, sizeof(d_s));
	//struct distance_sensor_s mb12xx_data1;
	//memset(&mb12xx_data1, 0, sizeof(mb12xx_data1));

	//static uint64_t T0 = 0, T1 = 0,count0 = 0,count1 = 0;
//	static uint64_t T0 = 0, count0 = 0;

	/*int sensor_sub_fd=orb_subscribe(ORB_ID(manual_control_setpoint));
	 struct manual_control_setpoint_s manual;
	 memset(&manual, 0, sizeof(manual));	*/
	/* one could wait for multiple topics with this technique, just using one here */
	px4_pollfd_struct_t fds[] = {
	//{ .fd = sensor_sub_fd,   .events = POLLIN },
			{ .fd = manual_sub, .events = POLLIN },
	/* there could be more file descriptors here, in the form like:
	 * { .fd = other_sub_fd,   .events = POLLIN },
	 */
	};

	int error_counter = 0;

	for (int i = 0; i < 1000; i++) {
		/* wait for sensor update of 1 file descriptor for 1000 ms (1 second) */
		int poll_ret = px4_poll(fds, 1, 300);
		/* handle the poll result */
		if (poll_ret == 0) {
			/* this means none of our providers is giving us data */
			PX4_ERR("Got no data within a second");

		} else if (poll_ret < 0) {
			/* this is seriously bad - should be an emergency */
			if (error_counter < 10 || error_counter % 50 == 0) {
				/* use a counter to prevent flooding (and slowing us down) */
				PX4_ERR("ERROR return value from poll(): %d", poll_ret);
			}
			error_counter++;
		} else {
			if (fds[0].revents & POLLIN) {
				/* obtained data for the first file descriptor */
				/* copy sensors raw data into local buffer */
				//orb_copy(ORB_ID(sonar_distance), sensor_sub_fd, &sonar);

//				orb_copy(ORB_ID(ekf_localization), sensor_sub_fd,
//						&mav_position);

				//orb_copy(ORB_ID(distance_sensor), sensor_distance_fd,&d_s);
				//orb_copy(ORB_ID(distance_sensor), mb12xx_sub_fd1,
				//		&mb12xx_data1);
				//orb_copy(ORB_ID(alt_ctrl), alt_ctrl_sub_, &alt_control);

				//printf("----------------------------------\n");
//				for (int j = 1; j <= 1; j++) {
					//printf("[Sonar] Range (%d)=%d(cm)\n",j-1,sonar.distance[j-1]);
					//printf("[Sonar] Status(%d)=%d\n",j-1,sonar.status[j-1]);
//					printf("[MB12xx0] dist1 = %.2f dist2 = %.2f\n",
//							(double) mb12xx_data0.distance[0],(double) mb12xx_data0.distance[1]);
//					printf("[MB12xx0] dist3 = %.2f dist4 = %.2f\n",
//							(double) mb12xx_data0.distance[2],(double) mb12xx_data0.distance[3]);
//					printf("[MB12xx0] dt = %.1f\n",
//							(double)((mb12xx_data0.timestamp-T0)/1000.0/(mb12xx_data0.count-count0)));

//					printf("[EKF] x = %.2f vx = %.2f y = %.2f vy = %.2f\n",
//							(double) mav_position.x, (double) mav_position.vx,
//							(double) mav_position.y, (double) mav_position.vy);

				orb_copy(ORB_ID(manual_control_setpoint),manual_sub,&manual);
				warnx("Manual:x=%.2f,y=%.2f,z=%.2f",(double)manual.x,(double)manual.y,(double)manual.z);

					//printf("distance_sensor.current_distance = %f",(double)d_s.current_distance);
//					printf("[MB12xx1] dist1 = %.2f T1 = %.1f \n",
//							(double) mb12xx_data1.current_distance,
//							(double)((mb12xx_data1.timestamp-T1)/1000.0/(mb12xx_data1.count-count1)));
//					printf("[Time] T0 = %lld T1 = %lld dt = %lld \n",
//							mb12xx_data0.timestamp/1000,mb12xx_data1.timestamp/1000,
//							(mb12xx_data1.timestamp-mb12xx_data0.timestamp)/1000);
					printf("-------------------------------\n");
//				}
//				T0 = mb12xx_data0.timestamp;
//				T1 = mb12xx_data1.timestamp;
//				count0 = mb12xx_data0.count;
//				count1 = mb12xx_data1.count;
//				time1 = hrt_absolute_time()/1000;
//				time_cha = time1-time2;
//				time2 = time1;
//				printf("Debug:time=%lld \n",time_cha);
				printf("=========Press CTRL+C to abort=========\n");
			}
		}
//		char c;
//		struct pollfd fds1;
//		int ret;
//		fds1.fd = 0;
//		fds1.events = POLLIN;
//		ret = poll(&fds1, 1, 0);
//		if (ret > 0) {
//			read(0, &c, 1);
//			if (c == 0x03 || c == 0x63 || c == 'q') {
//				warnx("User abort\n");
//				break;
//			}
//		}
		usleep(400000);
	}

	PX4_INFO("exiting");

	return 0;
}

