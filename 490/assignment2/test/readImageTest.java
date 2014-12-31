/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.awt.image.BufferedImage;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author tazzledazzle
 */
public class readImageTest {
    
    public readImageTest() {
    }
    
    @BeforeClass
    public static void setUpClass() {
    }
    
    @AfterClass
    public static void tearDownClass() {
    }
    
    @Before
    public void setUp() {
    }
    
    @After
    public void tearDown() {
    }

    /**
     * Test of getIntensity method, of class readImage.
     */
    @Test
    public void testGetIntensity() {
        System.out.println("getIntensity");
        BufferedImage image = null;
        int height = 0;
        int width = 0;
        readImage instance = new readImage();
        instance.getIntensity(image, height, width);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of getColorCode method, of class readImage.
     */
    @Test
    public void testGetColorCode() {
        System.out.println("getColorCode");
        BufferedImage image = null;
        int height = 0;
        int width = 0;
        readImage instance = new readImage();
        instance.getColorCode(image, height, width);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of writeColorCode method, of class readImage.
     */
    @Test
    public void testWriteColorCode() {
        System.out.println("writeColorCode");
        readImage instance = new readImage();
        instance.writeColorCode();
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of writeIntensity method, of class readImage.
     */
    @Test
    public void testWriteIntensity() {
        System.out.println("writeIntensity");
        readImage instance = new readImage();
        instance.writeIntensity();
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of main method, of class readImage.
     */
    @Test
    public void testMain() {
        System.out.println("main");
        String[] args = null;
        readImage.main(args);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }
    
}
