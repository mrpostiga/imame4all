package com.seleuco.mame4droid;

import java.net.InetAddress;
import java.net.NetworkInterface;
import java.util.Collections;
import java.util.Enumeration;
import java.util.List;

import org.apache.http.conn.util.InetAddressUtils;

import android.app.AlertDialog;
import android.app.Dialog;
import android.app.ProgressDialog;
import android.app.Service;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.net.wifi.WifiManager;
import android.view.View;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.EditText;
import android.widget.Toast;

import com.seleuco.mame4droid.helpers.MainHelper;
import com.seleuco.mame4droid.helpers.PrefsHelper;
import com.seleuco.mame4droid.R;


public class NetPlay {
		
	protected Dialog netplayDlg = null;
	
	protected ProgressDialog progressDialog = null; 
	
	private boolean canceled = false;	
	
	protected MAME4droid mm = null;
		
	public NetPlay(MAME4droid mm) {
		this.mm = mm;
	}
	
	DialogInterface.OnCancelListener dialogCancelListener = new DialogInterface.OnCancelListener() { 
		public void onCancel(DialogInterface dialog) { 									
			Emulator.resume();					
		} 
	};	
	
	protected void prepareButtons(){
		
		final Button startButton = (Button) netplayDlg.findViewById(R.id.StartGameBtn);
		final Button joinButton = (Button) netplayDlg.findViewById(R.id.JoinPeerGameBtn);
		final Button disconnectButton = (Button) netplayDlg.findViewById(R.id.DisconnectBtn);
		
		if(Emulator.getValue(Emulator.NETPLAY_HAS_CONNECTION)==1)
		{
			startButton.setEnabled(false);
			joinButton.setEnabled(false);
			disconnectButton.setEnabled(true);
		}
		else
		{
			startButton.setEnabled(true);
			joinButton.setEnabled(true);
			disconnectButton.setEnabled(false);		
		}		
		
		String name = Emulator.getValueStr(Emulator.GAME_SELECTED);
		if(name!=null && name.length()!=0)
		{
		   startButton.setText("Start game: "+name);		   
		}
		else
		{
			startButton.setText("Start game");
			startButton.setEnabled(false);
		}
	}
		
	public void createDialog() {
		
		netplayDlg = new Dialog(mm);

		netplayDlg.setContentView(R.layout.netplayview);
		netplayDlg.setTitle("Peer-To-Peer Netplay");
		netplayDlg.setCancelable(true);
		netplayDlg.setOnCancelListener(dialogCancelListener);

		final Button startButton = (Button) netplayDlg.findViewById(R.id.StartGameBtn);
		startButton.setOnClickListener(createGameClick);
		
		final Button joinButton = (Button) netplayDlg.findViewById(R.id.JoinPeerGameBtn);
		joinButton.setOnClickListener(joinGameClick);
		
		final Button disconnectButton = (Button) netplayDlg.findViewById(R.id.DisconnectBtn);
		disconnectButton.setOnClickListener(disconnectGameClick);
		
		prepareButtons();
		
		netplayDlg.show();
		
		/*
		final SharedPreferences sp = mm.getPrefsHelper().getSharedPreferences();
		 
		AlertDialog.Builder builder = new AlertDialog.Builder(mm);
		View checkBoxView = View.inflate(mm, R.layout.wifiwarnview, null);
		builder.setView(checkBoxView); 
		
		if (sp.getBoolean("warnWIFI", true) && mm.getMainHelper().getDeviceDetected() != MainHelper.DEVICE_OUYA) {

			CheckBox checkBox = (CheckBox) checkBoxView
					.findViewById(R.id.dontbotherCBox);
			checkBox.setOnCheckedChangeListener(new OnCheckedChangeListener() {
				@Override
				public void onCheckedChanged(CompoundButton buttonView,
						boolean isChecked) {
					SharedPreferences.Editor edit = sp.edit();
					edit.putBoolean("warnWIFI", !isChecked);
					edit.commit();
				}
			});

			builder.setTitle("Open Wi-Fi Settings?");
			builder.setPositiveButton("Yes",
					new DialogInterface.OnClickListener() {
						public void onClick(DialogInterface dialog, int id) {
							mm.startActivity(new Intent(
									WifiManager.ACTION_PICK_WIFI_NETWORK));
						}
					});
			builder.setNegativeButton("No",
					new DialogInterface.OnClickListener() {
						public void onClick(DialogInterface dialog, int id) {
							netplayDlg.show();
						}
					});
			builder.show();
		} else {
			netplayDlg.show();
		}
		*/
				
	}

    public  String getIPAddress() {
        try {
            Enumeration<NetworkInterface> ifaceList;
            NetworkInterface selectedIface = null;

            // First look for a WLAN interface
            ifaceList = NetworkInterface.getNetworkInterfaces();
            while (selectedIface == null && ifaceList.hasMoreElements()) {
                    NetworkInterface intf = ifaceList.nextElement();
                    if (intf.getName().startsWith("wlan")) {
                        List<InetAddress> addrs = Collections.list(intf.getInetAddresses());
                        for (InetAddress addr : addrs) {
                            if (!addr.isLoopbackAddress()) {
                                String sAddr = addr.getHostAddress().toUpperCase();
                                boolean isIPv4 = InetAddressUtils.isIPv4Address(sAddr);                         
                                if (isIPv4) 
                                    return sAddr;                        
                            }
                        }                                               	
                    }
            }

            // If we didn't find that, look for an Ethernet interface
            ifaceList = NetworkInterface.getNetworkInterfaces();
            while (selectedIface == null && ifaceList.hasMoreElements()) {
                    NetworkInterface intf = ifaceList.nextElement();
                    if (intf.getName().startsWith("eth")) {
                        List<InetAddress> addrs = Collections.list(intf.getInetAddresses());
                        for (InetAddress addr : addrs) {
                            if (!addr.isLoopbackAddress()) {
                                String sAddr = addr.getHostAddress().toUpperCase();
                                boolean isIPv4 = InetAddressUtils.isIPv4Address(sAddr);                         
                                if (isIPv4) 
                                    return sAddr;                        
                            }
                        }                                               	
                    }
            }       	
        	
            List<NetworkInterface> interfaces = Collections.list(NetworkInterface.getNetworkInterfaces());
            for (NetworkInterface intf : interfaces) {
                List<InetAddress> addrs = Collections.list(intf.getInetAddresses());
                for (InetAddress addr : addrs) {
                    if (!addr.isLoopbackAddress()) {
                        String sAddr = addr.getHostAddress().toUpperCase();
                        boolean isIPv4 = InetAddressUtils.isIPv4Address(sAddr);                         
                        if (isIPv4) 
                            return sAddr;                        
                    }
                }
            }
        } catch (Exception ex) { }
        return null;
    }
	
	Button.OnClickListener createGameClick = new Button.OnClickListener() {
		public void onClick(View v) {			
			createGame();			
		}
	};
	
	Button.OnClickListener joinGameClick = new Button.OnClickListener() {
		public void onClick(View v) {	
			AlertDialog.Builder alert = new AlertDialog.Builder(mm);

			alert.setTitle("Enter peer IP Address:");
			//alert.setMessage("Enter peer IP address:");

			final EditText input = new EditText(mm);
			alert.setView(input);
			
			String ip = mm.getPrefsHelper().getSharedPreferences().getString(PrefsHelper.PREF_NETPLAY_PEERADDR,"");
			
			input.setText(ip);
			input.setSelection(input.getText().length());

			alert.setPositiveButton("Ok", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int whichButton) {
			     String ip = input.getText().toString();
			     
			     if(ip==null || ip.length()==0)
			     {
					Toast.makeText(mm, "Invalid peer IP!",Toast.LENGTH_SHORT).show();
					return;
			     }
	
			     InputMethodManager imm = (InputMethodManager)mm.getSystemService(Service.INPUT_METHOD_SERVICE);
			     imm.hideSoftInputFromWindow(input.getWindowToken(), 0);
			     
			     SharedPreferences sp = mm.getPrefsHelper().getSharedPreferences();
			     Editor edit = sp.edit();
				 edit.putString(PrefsHelper.PREF_NETPLAY_PEERADDR,ip);
				 edit.commit();
				 
			     joinGame(ip);
			  }
			});

			alert.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
			  public void onClick(DialogInterface dialog, int whichButton) {
			    // Canceled.
			  }
			});

			AlertDialog dlg = alert.create();					
			dlg.getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_HIDDEN);
			dlg.show();					
		}
	};
	
	Button.OnClickListener disconnectGameClick = new Button.OnClickListener() {
		public void onClick(View v) {			
			Emulator.setValue(Emulator.NETPLAY_HAS_CONNECTION, 0);
			Toast.makeText(mm, "Disconnected from Netplay",Toast.LENGTH_SHORT).show();	
			prepareButtons();
		}
	};	
	
	public void createGame() {
		
		String strPort = mm.getPrefsHelper().getNetplayPort();		
		int port = 0;
		try{port = Integer.parseInt(strPort);}catch(Exception e){}
		if(!(port>=1024 && port <= 32768*2)){
			Toast.makeText(mm, "Invalid Port",Toast.LENGTH_SHORT).show();
			return;
		}

		if (Emulator.netplayInit(null, port, 0) == -1) {
			Toast.makeText(mm, "Error initializing Netplay!",Toast.LENGTH_SHORT).show();
			return;
		}
		
		//netplayDlg.hide();

		canceled = false;
		progressDialog = ProgressDialog.show(mm, "Press back to cancel",
				"Creating game at ...", true, true,
				new DialogInterface.OnCancelListener() {
					@Override
					public void onCancel(DialogInterface dialog) {
						canceled = true;
					}
				});

		Thread t = new Thread(new Runnable() {
			public void run() {
				final String ip = getIPAddress(); 
				if(ip==null)
				{
					try {
						Thread.sleep(2000);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
					canceled = true;
			    	mm.runOnUiThread(new Runnable() {
			            public void run() {
			            	Toast.makeText(mm, "No IP address available!. Is Wi-Fi enabled?",Toast.LENGTH_LONG).show();
			            }
			    	});					
				}
		    	mm.runOnUiThread(new Runnable() {
		            public void run() {
		            	 progressDialog.setMessage("Waiting for peer...\nCreating game at :" + ip );
		            }
		    	});					  
				while (Emulator.getValue(Emulator.NETPLAY_HAS_JOINED) == 0 && !canceled) {
					try {
						Thread.sleep(1000);
						//System.out.println("Esperando...");
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}

				if (progressDialog != null && progressDialog.isShowing()) {
					progressDialog.dismiss();
				}

				if (canceled) {
					Emulator.setValue(Emulator.NETPLAY_HAS_CONNECTION, 0);
				} else {
					Emulator.setValue(Emulator.EXIT_GAME_KEY, 1);
				}
		    	mm.runOnUiThread(new Runnable() {
		            public void run() {
		            	if(!canceled)
		            	{
		            		if(netplayDlg.isShowing())
		            		  netplayDlg.hide();
		            		Toast.makeText(mm, "Connected. Starting Netplay!",Toast.LENGTH_SHORT).show();			            		
		            		Emulator.resume();
		            	}
		            }
		    	});					
			}
		});
		t.start();
	}
    
    public void joinGame(String addr){

		String strPort = mm.getPrefsHelper().getNetplayPort();		
		int port = 0;
		try{port = Integer.parseInt(strPort);}catch(Exception e){}
		if(!(port>=1024 && port <= 32768*2)){
			Toast.makeText(mm, "Invalid Port",Toast.LENGTH_SHORT).show();
			return;
		}
		
		if (Emulator.netplayInit(addr, port, 0) == -1) {
			Toast.makeText(mm, "Error initializing Netplay!",
					Toast.LENGTH_SHORT).show();
			return;
		}
		
		//netplayDlg.hide();
		
		canceled = false;
		progressDialog = ProgressDialog.show(mm, "Press back to cancel",
				"Connecting to :" + addr, true, true,
				new DialogInterface.OnCancelListener() {
					@Override
					public void onCancel(DialogInterface dialog) {
						canceled = true;
					}
				});

		Thread t = new Thread(new Runnable() {
			public void run() {
				while (Emulator.getValue(Emulator.NETPLAY_HAS_JOINED) == 0
						&& !canceled) {
					try {
						if (Emulator.netplayInit(null, 0, 1) == -1)
							canceled = true;
						Thread.sleep(1000);
						//System.out.println("Esperando...");
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}

				if (progressDialog != null && progressDialog.isShowing()) {
					progressDialog.dismiss();
				}

				if (canceled) {
					Emulator.setValue(Emulator.NETPLAY_HAS_CONNECTION, 0);
				} else {
					Emulator.setValue(Emulator.EXIT_GAME_KEY, 1);
				}
				
		    	mm.runOnUiThread(new Runnable() {
		            public void run() {
		            	if(!canceled)
		            	{
		            		if(netplayDlg.isShowing())
			            		  netplayDlg.hide();
		            		Toast.makeText(mm, "Connected. Starting Netplay!",Toast.LENGTH_SHORT).show();
		            		Emulator.resume();
		            	}
		            }
		    	});	
			}
		});
		t.start();    	   		
    }
    
}
