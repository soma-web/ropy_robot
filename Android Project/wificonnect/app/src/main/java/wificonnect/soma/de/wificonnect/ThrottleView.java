package wificonnect.soma.de.wificonnect;

import android.content.Context;
import android.content.res.TypedArray;
import android.support.v4.view.MotionEventCompat;
import android.util.AttributeSet;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class ThrottleView extends RelativeLayout {

    private static final String TAG = "ThrottleView";
    private TextView mImage;

    public ThrottleView(Context context) {
        super(context);
        init(context, null);
    }

    public ThrottleView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context, attrs);
    }

    public ThrottleView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(context, attrs);
    }

    public ThrottleView(Context context, AttributeSet attrs, int defStyleAttr, int defStyleRes) {
        super(context, attrs, defStyleAttr, defStyleRes);
        init(context, attrs);
    }

    private void init(Context context, AttributeSet attrs)
    {
        LayoutInflater inflater = (LayoutInflater) context
                .getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        inflater.inflate(R.layout.throttle_view, this, true);
        mImage = findViewById(R.id.img_throttle);
    }

    @Override
    public boolean onInterceptTouchEvent(MotionEvent ev) {
        /*
         * This method JUST determines whether we want to intercept the motion.
         * If we return true, onTouchEvent will be called and we do the actual
         * scrolling there.
         */


        final int action = MotionEventCompat.getActionMasked(ev);

        // Always handle the case of the touch gesture being complete.
        if (action == MotionEvent.ACTION_CANCEL || action == MotionEvent.ACTION_UP) {
            // Release the scroll.

            return false; // Do not intercept touch event, let the child handle it
        }

        switch (action) {
            case MotionEvent.ACTION_MOVE: {
                break;
            }
        }


        return false;
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        int viewWidth = this.getWidth();
        int viewHeight = this.getHeight();
        float pivotY = this.getPivotY();
        int[] locationOnScreen = new int[2];
        this.getLocationOnScreen(locationOnScreen);
        int xOnScreen = locationOnScreen[0];
        int yOnScreen = locationOnScreen[1];


        LayoutParams layoutParams = (LayoutParams) mImage.getLayoutParams();
        switch (event.getAction()){
            case MotionEvent.ACTION_DOWN:
                //Log.d(TAG, "xOnScreen "  + xOnScreen + " yOnScreen " +  yOnScreen + " viewHeight " + getHeight());
                break;
            case MotionEvent.ACTION_MOVE:
                layoutParams.addRule(RelativeLayout.ALIGN_PARENT_TOP, RelativeLayout.TRUE);

                int touchX = (int) event.getRawX();
                int touchY = (int) event.getRawY();

                int topMargin = touchY - yOnScreen;
                topMargin = Math.min(getHeight() - mImage.getHeight(), topMargin);
                topMargin = Math.max(0, topMargin);
                layoutParams.topMargin = topMargin;
                //Log.d(TAG, "touchX " + touchX + " touchY " + touchY + " topMargin " + topMargin);
                break;
            case MotionEvent.ACTION_CANCEL:
            case MotionEvent.ACTION_UP:
                layoutParams = Reset(layoutParams);
                break;
        }
        mImage.setLayoutParams(layoutParams);
        mImage.invalidate();
        invalidate();
        return true;
    }

    private LayoutParams Reset(LayoutParams layoutParams) {
        Log.d(TAG, "resetting");
        layoutParams.topMargin = getHeight()/2;
        layoutParams.bottomMargin = 0;
        layoutParams.addRule(RelativeLayout.ALIGN_PARENT_TOP, RelativeLayout.CENTER_IN_PARENT);
        return layoutParams;
    }


}
